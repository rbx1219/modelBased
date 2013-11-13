// -*- c++ -*- 
//
//  File:         mpm.hpp
//
//  Description:  C++ interface to the class mpm.
//                mpm stands for Marginal Product Model (see Harik's paper).
//
//  Author:       Fernando Lobo
//
//  Date:         June/1999
//
//  Modified to be compliant with gcc 3.4 by Kumara Sastry
//  Date:        March/2006

#ifndef _mpm_hpp
#define _mpm_hpp

#include <iostream>
#include <fstream>

#include "subset.hpp"
#include "population.hpp"


class population;
class mpm
{
  private:
    int     maxSets;      // maximum number of sets in the cache
    int     n_subsets;    // number of subsets
    subset  *subsets;     // the subsets
    double  mc;   // model complexity
    double  cpc;  // compressed population complexity

  public:
    mpm( const mpm &in ){
	subsets = new subset[in.n_subsets];
	for(int i = 0 ; i < in.n_subsets ; i++)
		subsets[i] = in[i];
		printf("Jizz\n");
	}
    mpm( int n_sets );
    ~mpm();
    int num_subsets() { return n_subsets; }
    subset & operator[](const int i) const { return subsets[i]; }
    void insert( subset &S );
    void remove( int i );
    void merge( int i, int j, subset &S );
    bool converged() { return mc==0; }
    friend std::ostream &operator<< (std::ostream &out, mpm &MPM);
 
    double MC() { return mc; }
    double CPC() { return cpc; }
    double CC() { return mc + cpc; }
    double modelComplexity();
    double compressedPopulationComplexity();
    void combinedComplexity();

    void model( population *pop, std::ofstream &outfile );
    void generate( population *oldpop, population *newpop );
};


#endif
