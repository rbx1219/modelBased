// -*- c++ -*- 
//
//  File:         cache.hpp
//
//  Description:  C++ interface for the class cache.
//                The cache is used to speed up the MPM search
//                as suggested in Harik's paper.
//
//  Author:       Fernando Lobo
//
//  Date:         June/1999
//
//  Modified to be compliant with gcc 3.4 by Kumara Sastry
//  Date:        March/2006

#ifndef _cache_hpp
#define _cache_hpp

#include <iostream>
#include "subset.hpp"
#include "mpm.hpp"

class cache
{
private:
  long maxSz;        // maximum size of the cache ( ell*(ell+1)/2)
  long sz;           // number of subsets stored in the cache
  long *E;           // a collection of empty cache entries
  long Esize;        // number of elements of E

public:

  subset *mergedSet;   // an array of subsets
  int *subset1_id;     // mergedSet = subset1 UNION subset2 
  int *subset2_id;     // ids refer to MPM subsets

  cache();
  ~cache();
  long size() { return sz; }
  void insert( int id1, int id2, subset &S, int popsize );
  void removeEntry( int id );
  void replace_X_by_Y( int x, int y );
  void compact();
  friend std::ostream &operator<< (std::ostream &out, cache &C);
};


#endif
