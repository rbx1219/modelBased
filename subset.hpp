// -*- c++ -*- 
//
//  File:         subset.hpp
//
//  Description:  C++ interface to the class subset.
//                (a subset of the MPM)
//
//  Author:       Fernando Lobo
//
//  Date:         June/1999
//
//  Modified to be compliant with gcc 3.4 by Kumara Sastry
//  Date:        March/2006

#ifndef _subset_hpp
#define _subset_hpp

#include <iostream>
#include "intlist.hpp"
#include "population.hpp"

class subset
{
  private:
    intList L;         // a subset 
    long num_counts;   // 2 ^ L.length() 
    double mc;   // model complexity
    double cpc;  // compressed population complexity
  public:
    subset();
    ~subset();
    subset & operator=(subset &S);
    int size() { return L.length(); }
    long numCounts() { return num_counts; }
    long *counts;      // the frequency counts  (2 ^ L.length() ) 
    void space_for_counts( int popsize );
    void insert( int elem ) { L.insert( elem ); }
    void asArray( int *A ) { L.asArray( A ); }
    void merge( subset &S1, subset &S2 );
    friend std::ostream &operator<< (std::ostream &out, subset &S);
    

    double MC() { return mc; }
    double CPC() { return cpc; }
    double CC() { return mc + cpc; }
    double modelComplexity( int popsize );
    double compressedPopulationComplexity( int popsize );
    void combinedComplexity( int popsize );
    void compute_freq_counts( population &pop );

};

#endif



