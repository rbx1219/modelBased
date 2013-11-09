// -*- c++ -*-
//
//  File:         utility.hpp
//
//  Description:  utility functions and procedures.
//
//  Author:       Fernando Lobo
//
//  Date:         June/1999
//
//  Modified to be compliant with gcc 3.4 by Kumara Sastry
//  Date:        March/2006
 
#ifndef _utility_hpp
#define _utility_hpp

#include <stdio.h>
#include <fstream>

void    error( char *msg );
void    errorcheck( char *str, bool condition );
double  sqr( double x );
double  min( double x );
int     min( int x, int y );
int     max( int x, int y );
long    decode( int *str, int lbits );
void    encode( int x, int nbits, int *str );
double  log( double x, double b );
void    mergeSort( int *A, int sizeA, int *B, int sizeB, int *C );
void    makeshuffle( int *shufflearray, const int n );



#endif

