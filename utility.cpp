// -*- c++ -*-
//
//  File:         utility.cpp
//
//  Description:  utility functions and procedures.
//
//  Author:       Fernando Lobo
//
//  Date:         June/1999
//
//  Modified to be compliant with gcc 3.4 by Kumara Sastry
//  Date:        March/2006
  
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <math.h>

#include "utility.hpp"
#include "random.hpp"

extern randomG RANDOM;

// outputs an error msg and stops the program 
void error( char *msg )
{
  std::cout << msg << std::endl;
  exit(1);
}

// if 'condition' is false, print an error message and abort the program
void errorcheck( char *str, bool condition )
{
  if( !condition )
    {
      std::cout << "ERROR: " << str << std::endl;
      exit( 1 );
    }
}

double sqr( double x )
{
  return x*x;
}

int min( int x, int y )
{
  if (x<y) return x;
  else return y;
}

int max( int x, int y )
{
  if (x>y) return x;
  else return y;
}

// Decode string as unsigned binary integer
long decode( int *str, int lbits )
{
  int j;
  long accum, powerof2;

  accum = 0; powerof2 = 1;
  for( j = lbits-1; j>= 0; j-- )
    {
      if( str[j]==1 ) accum += powerof2;
      powerof2 *= 2;
    }
  return accum;
}

// Encode x as a binary integer of 'nbits'
// ex: x=9, nbits=4  ===>  str=1001
void encode( int x, int nbits, int *str )
{
  int i;
  for( i=0; i<nbits; i++ ) str[i] = 0;
  i = nbits-1;
  while( x != 0 && i >= 0 )
    {
      str[i] = x%2;
      x = x/2;
      i--;
    }
}
  
// return log x base b
double log( double x, double b )
{
  return log(x)/log(b); 
}

// merge arrays A and B into array C.
// both A and B are sorted.
// C will be sorted at the end.
//
void mergeSort( int *A, int sizeA, int *B, int sizeB, int *C )
{
  int sizeC = sizeA + sizeB;
  int a=0,b=0,c=0;
  while( c < sizeC )
    {
      if( a >= sizeA || b >= sizeB ) break;
      if( A[a] < B[b] )
	{
	  C[c] = A[a];
	  a++;
	}
      else
	{
	  C[c] = B[b];
	  b++;
	}
      c++;
    }
  if( a >= sizeA )
    // copy elements from B
    for( int i=b; i< sizeB; i++ )
      {
	C[c] = B[i];
	c++;
      }
  if( b >= sizeB )
    // copy elements from A
    for( int i=a; i< sizeA; i++ )
      {
	C[c] = A[i];
	c++;
      }
}
  
// make a random n-permutation of the numbers 0,1,2,...,n-1
void makeshuffle( int *shufflearray, const int n )
{
  int i;

  // initialize
  for( i=0; i<n; i++ ) shufflearray[i] = i;
  // shuffle
  for( i=0; i<n-1; i++ )
    {
      int other = RANDOM.uniform( i, n-1 );
      // swap( shufflearray[other], shufflearray[i] );   
      int temp = shufflearray[other];
      shufflearray[other] = shufflearray[i];
      shufflearray[i] = temp;
    }
}

