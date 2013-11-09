// -*- c++ -*-
//
//  File:         gene.hpp
//
//  Description:  C++ interface for the class gene.
//                A gene stores an allele, 0 or 1.
//
//  Author:       Fernando Lobo
//
//  Date:         June/1999
//
//  Modified to be compliant with gcc 3.4 by Kumara Sastry
//  Date:        March/2006

#ifndef _gene_hpp
#define _gene_hpp

#include <iostream>
#include "random.hpp"

class gene  
{
  private:
    int Allele;  
  public:
    gene() {}
    gene( const int v ) { Allele = v; }
    gene( const gene &g ) { Allele = g.Allele; }
    ~gene() {}
    void random( double prob=0.5 );
    int allele() { return Allele; }
    gene & operator=(const gene &g);
    gene & operator=(const int v );
    int operator==(const gene &g) { return Allele == g.Allele; }
    int operator==(const int v)   { return Allele == v; }
    int operator!=(const gene &g) { return Allele != g.Allele; }
    int operator!=(const int v)   { return Allele != v; }
    void mutate();
    friend std::ostream &operator<< (std::ostream &out, const gene &g);
};



#endif
