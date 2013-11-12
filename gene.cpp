// -*- c++ -*-
//
//  File:         gene.cpp
//
//  Description:  C++ implementation for the class gene.
//                A gene stores an allele, 0 or 1.
//
//  Author:       Fernando Lobo
//
//  Date:         June/1999
//
//  Modified to be compliant with gcc 3.4 by Kumara Sastry
//  Date:        March/2006

#include <assert.h>
#include <iostream>
#include "gene.hpp"
#include "random.hpp"      // random number generator

extern randomG RANDOM;
 
// generate an allele randomly
void gene::random( double prob )
{ 
  if( RANDOM.flip( prob ) )
    Allele=1;
  else
    Allele=0;
}

// print the gene
std::ostream &operator<< (std::ostream &out, const gene &g)
{
  out << g.Allele; 
  return out;
}

// assignment operator: gene = gene
gene & gene::operator=(const gene &g)
{
  if (this== &g) return *this;
  Allele = g.Allele;
  return *this;
}

// assignment operator: gene = int
gene & gene::operator=(const int v)
{
  Allele = v;
  return *this;
}

// flips 0 to 1 or 1 to 0.
void gene::mutate()
{
  Allele = !Allele;
}
