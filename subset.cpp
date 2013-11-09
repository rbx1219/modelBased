// -*- c++ -*- 
//
//  File:         subset.cpp
//
//  Description:  C++ implementation of the class subset.
//                (a subset of the MPM)
//
//  Author:       Fernando Lobo
//
//  Date:         June/1999
//
//  Modified to be compliant with gcc 3.4 by Kumara Sastry
//  Date:        March/2006

#include <iostream>
#include <math.h>
#include <stdlib.h>

#include "subset.hpp"
#include "parameter.hpp"
#include "utility.hpp"
#include "population.hpp"

//
// constructor
//
subset::subset()
  : L()
{
  counts = NULL;
  num_counts = 0;
  mc = 0;
  cpc = 0;
}

//
// destructor
//
subset::~subset()
{
  delete [] counts;  // free memory
}

//
// assignment operator
//
subset & subset::operator=(subset &S)
{
  if (this == &S)
    return *this;

  L = S.L;
  num_counts = S.num_counts;
  mc = S.mc;
  cpc = S.cpc;

  delete [] counts;
  counts = new long[ num_counts ];  
  for( int i=0; i< num_counts; i++ ) 
    counts[i] = S.counts[i];
  
  return *this;
}

//
// merge subsets S1 and S2 
// both S1 and S2 are sorted. 
//
void subset::merge( subset &S1, subset &S2 )
{
  int sizeS1 = S1.size();
  int *A1 = new int [ sizeS1 ];
  S1.asArray( A1 );
 
  int sizeS2 = S2.size();
  int *A2 = new int [ sizeS2 ];
  S2.asArray( A2 );

  int Asize = sizeS1 + sizeS2;
  int *A = new int [ Asize ];
  
  mergeSort( A1, sizeS1, A2, sizeS2, A );
  //
  // insert elements of A in this set
  //
  for( int i=Asize-1; i>=0; i-- )
    insert( A[i] );

  delete [] A;
  delete [] A1;
  delete [] A2;  
}

//
// allocates spaces for the frequency counts.
//
void subset::space_for_counts( int popsize )
{
  assert( pow(2,size()) <= popsize );
  delete [] counts;  // free memory
  num_counts = long( pow(2,size()) );
  counts = new long[ num_counts ];  // allocate memory
  for( int i=0; i< num_counts; i++ ) 
    counts[i] = 0;
}

// print the subset
std::ostream &operator<< (std::ostream &out, subset &S)
{
  out << S.L;
  return out;
}

//
// returns the number of bits needed to store the model
// for this subset.
// 
double subset::modelComplexity( int popsize )
{
  return log( 1 + popsize, 2 ) * (num_counts - 1);
}

//
// returns the number of bits needed to store this subset of bits
// across the whole population.
//
double subset::compressedPopulationComplexity( int popsize )
{
  double entropy = 0;
  for( int j=0; j< num_counts; j++ )
    {
      double prob = double(counts[j]) / popsize;
      if( prob != 0 )
	entropy += -prob * log(prob,2);
    }
  //
  // entropy gives the avg. number of bits needed to store this subset of bits
  // per individual under the current model
  // 
  return entropy * popsize;
}

//
// compute the combined complexity
//
void subset::combinedComplexity( int popsize )
{
  mc = modelComplexity( popsize );
  cpc = compressedPopulationComplexity( popsize );
}

//
// compute the frequency counts for this subset of genes
//
void subset::compute_freq_counts( population &pop )
{
  int S = size();
  long twoToTheS = numCounts();
  int *set = new int [S];
  this->asArray( set );
  int *schema = new int [ S ];
  long p;

  for( int i=0; i< pop.popsize(); i++ )
    {
      for( int j=0; j< S; j++ )
	{
	  int locus = set[j];
	  int allele = pop[i][locus].allele();
	  schema[j] = allele;
	}
      p = decode( schema, S ); 
      assert( p>=0 && p<twoToTheS );
      counts[p]++;
    }
  delete [] set;
  delete [] schema;
}




