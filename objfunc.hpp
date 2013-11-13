// -*- c++ -*-
//
//  File:         objfunc.hpp
//
//  Description:  Contains the objective function.
//                Change this for different problems.
//
//  Author:       Fernando Lobo
//
//  Date:         June/1999
//
//  Modified to be compliant with gcc 3.4 by Kumara Sastry
//  Date:        March/2006

#ifndef _objfunc_hpp
#define _objfunc_hpp

#include "model.hpp"
#include "chromosome.hpp"

double objfunc( chromosome &x );
double objfunc( chromosome &x , model *M);
double objective_func( char *chrom, int lchrom );
double objective_func(char *chrom , int lchrom , model* M);
#endif



