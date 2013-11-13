// -*- c++ -*- 
//
//  File:         chromosome.cpp
//
//  Description:  C++ implementation for the class chromosome.
//                A chromosome is an array of genes.      
//
//  Author:       Fernando Lobo
//
//  Date:         June/1999
//
//  Modified to be compliant with gcc 3.4 by Kumara Sastry
//  Date:        March/2006

#include <iostream>
#include <iomanip>
#include <assert.h>

#include "random.hpp"
#include "chromosome.hpp"
#include "gene.hpp"
#include "parameter.hpp"
#include "objfunc.hpp"

extern randomG RANDOM;

// initializes a chromosome. alleles are not initialized.
chromosome::chromosome( int ell )
{
  Length = ell;
  genes = new gene[ Length ]; // allocate memory
  Fitness = 0;
}

// copy constructor
chromosome::chromosome(const chromosome &chrom)
{
  genes = new gene[ chrom.Length ];  // allocate memory

  for( int i=0; i< chrom.Length; i++ )     // copy the genes
    genes[i] = chrom.genes[i];
    
  Length = chrom.Length;  
  Fitness = chrom.Fitness;
}

// destructor
chromosome::~chromosome()
{
  delete [] genes;  // free memory
}

// set the genes of the chromosome with random alleles
void chromosome::random()
{
  for( int i=0; i< Length; i++ )
    genes[i].random();
}

// assignment operator
chromosome & chromosome::operator=(const chromosome &chrom)
{
  if (this == &chrom)
    return *this;

  for( int i=0; i< chrom.Length; i++ )     // copy the genes
    genes[i] = chrom.genes[i];
  
  Length = chrom.Length;
  Fitness = chrom.Fitness;

  return *this;
}

// randomly mutates the genes of this chromosome.
void chromosome::mutate(double pmut)
{
  for( int i=0; i< Length; i++)
    if (RANDOM.flip(pmut))                        // toss a biased coined
      genes[i].mutate();
}


//
// Convert a chromosome to a character string.
// Storage for string must be allocated beforehand.
//
void chromosome::asString( char *str )
{
  int size = Length;
  for( int i=0; i< size; i++ )
    if( genes[i] == 1 )
      str[i] = '1';
    else
      str[i] = '0';
}

//
// copy 'n' genes specified by 'locus' of chromosome 'C' into this chromosome
//
void chromosome::copyGenes( chromosome &C, int *locus, int n )
{
  for( int i=0; i< n; i++ )
    genes[ locus[i] ] = C.genes[ locus[i] ];
}

// print the chromosome
std::ostream &operator<< (std::ostream &out, chromosome &chrom)
{
  if( parameter::report_string )
    for( int i=0; i< chrom.Length; i++)
      out << chrom.genes[i];
  if( parameter::report_fitness )   out << "   f= " << chrom.Fitness;
  
  return out;
}

// evaluate fitness function
void chromosome::evaluate() { Fitness = objfunc(*this); };
void chromosome::evaluate(model *M){Fitness = objfunc(*this , M);};
