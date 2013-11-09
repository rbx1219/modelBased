// -*- c++ -*- 
//
//  File:         mpm.cpp
//
//  Description:  C++ implementation for the class mpm.
//                mpm stands for Marginal Product Model (see Harik's paper).
//
//  Author:       Fernando Lobo
//
//  Date:         June/1999
//

#include <iostream>
#include <fstream>
#include <assert.h>
#include <math.h>

#include "mpm.hpp"
#include "subset.hpp"
#include "cache.hpp"
#include "utility.hpp"
#include "parameter.hpp"

// initializes an mpm.
mpm::mpm( int n_sets )
{
  maxSets = n_sets;
  subsets = new subset [maxSets];
  n_subsets = 0;
  mc = 0;
  cpc = 0;
}

// destructor
mpm::~mpm()
{
  delete [] subsets;  // free memory
}

void mpm::insert( subset &S )
{
  assert( n_subsets <= maxSets );
  subsets[ n_subsets ] = S;
  n_subsets++;
}
    
// remove Ith set
void mpm::remove( int j )
{
  subset empty;
  assert( j>=0 && j<n_subsets);
  subsets[j] = subsets[ n_subsets - 1 ];
  subsets[ n_subsets - 1 ] = empty;
  n_subsets--;
}


void mpm::merge( int i, int j, subset &S )
{
  assert( i>=0 && i<n_subsets);
  assert( j>=0 && j<n_subsets);
  assert( i < j );
  mc += S.MC() - subsets[i].MC() - subsets[j].MC();
  cpc += S.CPC() - subsets[i].CPC() - subsets[j].CPC();
  subsets[ i ] = S;
  remove( j );
} 

// print the mpm
std::ostream &operator<< (std::ostream &out, mpm &MPM)
{
  out << "[ ";
  for( int i=0; i< MPM.num_subsets()-1; i++ ) 
    out << MPM[i] << "- ";
  if( MPM.num_subsets() > 0 )
    out << MPM[ MPM.num_subsets()-1 ];
  out << " ], CC(MPM) = " << MPM.CC() << std::endl;
  return out;
}

// computes the model complexity of the mpm.
double mpm::modelComplexity()
{
  double sum = 0;
  for( int i=0; i< n_subsets; i++ ) 
    sum += subsets[i].MC();
  return sum;
}

// computes the compressed population compression under this mpm.
double mpm::compressedPopulationComplexity()
{
  double sum = 0;
  for( int i=0; i< n_subsets; i++ ) 
    sum += subsets[i].CPC();
  return sum;
}

// compute the combined complexity
void mpm::combinedComplexity()
{
  mc = modelComplexity();
  cpc = compressedPopulationComplexity();
}

// model population using a greedy MPM search
void mpm::model( population *pop, std::ofstream &outfile )
{
  //
  // initial MPM is [0][1][2]...[ell-1].
  //
  for( int i=0; i< parameter::lchrom; i++ )
    {
      subset S;
      S.insert(i);
      S.space_for_counts( pop->popsize() );
      S.compute_freq_counts( *pop );
      S.combinedComplexity( pop->popsize() );
      insert( S );
    }
  combinedComplexity();

  if( parameter::learn_MPM )
    {
      //
      // the cache is initialized with all pairs of subsets of the MPM.
      //
      cache Cache;
      for( int i=0; i< num_subsets()-1; i++ )
	for( int j=i+1; j< num_subsets(); j++ )
	  {
	    subset S1, S2, S3;
	    S1 = subsets[i];
	    S2 = subsets[j];
	    S3.merge(S1,S2);
	    S3.space_for_counts( pop->popsize() );
	    S3.compute_freq_counts( *pop );
	    S3.combinedComplexity( pop->popsize() );
	    Cache.insert( i, j, S3, pop->popsize() );
	  }
      //
      // do greedy search.
      // all information is in the cache.
      //
      while( true ) {
	if( parameter::report_MPM ) outfile << "MPM : " << *this << std::endl;
	int bestCompressionID = -1;  // -1 means it's not possible to compress the population
	double bestCompression = 0;
	for( int i=0; i< Cache.size(); i++ )
	  {
	    double comp1 = subsets[ Cache.subset1_id[i] ].CC();
	    double comp2 = subsets[ Cache.subset2_id[i] ].CC();
	    double comp12 = Cache.mergedSet[i].CC();
	    double compression = comp1 + comp2 - comp12;
	    if( compression > bestCompression ) {
	      bestCompression = compression;
	      bestCompressionID = i;
	    }
	  }
	
	if( bestCompressionID == -1 ) 
	  {
	    // it's not possible to compress the population.
	    // stop searching for MPM.
	    break;
	  }
	else
	  // do the merging corresponding to the cache entry
	  // and do the necessary updates on the cache.
	  {
	    //
	    // update MPM
	    //
	    int s1 = Cache.subset1_id[ bestCompressionID ];
	    int s2 = Cache.subset2_id[ bestCompressionID ];
	    int minimum = min( s1,s2 );
	    int maximum = max( s1,s2 );
	    merge( minimum, maximum, Cache.mergedSet[ bestCompressionID ] );
	    //
	    // update cache
	    //
	    Cache.removeEntry( minimum );
	    Cache.removeEntry( maximum );
	    Cache.replace_X_by_Y( num_subsets(), maximum );
	    //
	    // create the new subsets
	    //
	    subset S[ num_subsets() - 1 ];
	    int k=0;
	    for( int i=0; i< num_subsets(); i++ )
	      {
		if( i== minimum ) continue;
		S[k].merge( subsets[minimum], subsets[i] );
		//
		// if merged set is too big, (has more frequency counts 
		// than the popsize), then don't include it in the cache.
		// Just discard it.
		// 
		if( pow(2,S[k].size()) > pop->popsize() ) 
		  {
		    k++;
		    continue;
		  }
		S[k].space_for_counts( pop->popsize() );
		S[k].compute_freq_counts( *pop );
		S[k].combinedComplexity( pop->popsize() );
		Cache.insert( min(i,minimum), max(i,minimum), S[k], pop->popsize() );
		k++;
	      }
	    Cache.compact();
	  }
      }
    } // end if( parameter::learn_MPM )
}

// generate a new population according to this MPM model
void mpm::generate( population *oldpop, population *newpop )
{
  int i;
  int popsize;

  assert( oldpop->popsize() == newpop->popsize() );
  popsize = oldpop->popsize();

  // we will generate N individuals through "crossover".
  int N = int( parameter::pcross * popsize );

  //
  // this part is "equivalent" to perfect mixing 
  // among the subsets of the MPM.
  // 
 int shuffle[ N ];
  for( i=0; i< num_subsets(); i++ )
    {
      subset S;
      S = subsets[i];
      int nbits = S.size();
      int *locus = new int[ nbits ];
      S.asArray( locus );

      makeshuffle( shuffle, N );
      for( int j=0; j< N; j++ )
	(*newpop)[j].copyGenes( (*oldpop)[shuffle[j]], locus, nbits );
      delete [] locus;
    }
  //
  // now keep the remaining individuals
  //
  for( int j=N; j< popsize; j++ )
    (*newpop)[j] = (*oldpop)[j];
}



