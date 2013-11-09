// -*- c++ -*- 
//
//  File:         chromosome.hpp
//
//  Description:  C++ interface for the class chromosome.
//                A chromosome is an array of genes.      
//
//  Author:       Fernando Lobo
// 
//  Date:         June/1999
//
//  Modified to be compliant with gcc 3.4 by Kumara Sastry
//  Date:        March/2006


#ifndef _chromosome_hpp
#define _chromosome_hpp

#include <iostream>
#include "gene.hpp"
#include "parameter.hpp"

class chromosome
{
  private:
    gene   *genes;        // the genes
    int    Length;
    double Fitness;       // fitness value
  public:
    chromosome( int ell = parameter::lchrom );
    chromosome(const chromosome &chrom);
    ~chromosome();
    double fitness() { return Fitness; }
    void set_fitness( double fit ) { Fitness = fit; }
    void evaluate();
    void random();
    void mutate(double pmut);
    int  length() { return Length; }
    void asString( char *str );
    void copyGenes( chromosome &C, int *locus, int n );
    chromosome & operator=(const chromosome &chrom);
    gene & operator[](int loci) { return genes[loci]; }
    friend std::ostream &operator<< (std::ostream &out, chromosome &chrom);
};

#endif
