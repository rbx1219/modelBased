// -*- c++ -*-
//
//  File:         objfunc.cpp
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

#include "objfunc.hpp"
#include "chromosome.hpp"
#include "parameter.hpp"
#include "model.hpp"

#include <stdio.h>
#include <stdlib.h>

double objfunc( chromosome &x )
{
	//
	// convert chromosome to a charater string
	//
	char *str = new char [ x.length() ];
	x.asString( str );

	//
	// call objective function
	//    
	double v = objective_func( str, x.length() );
	delete [] str;
	return v;
}

double objfunc(chromosome &x ,model *M)
{
	char *str = new char[ x.length() ];
	x.asString(str);

	double v = objective_func(str , x.length() , M);
	delete[] str;
	return v;
}

//------------------------------------------------------------


// unitation function. return the number of 1's
int unitation( char *chrom, int startBit, int endBit )
{
	int ones = 0;
	for( int i=startBit; i<= endBit; i++ )
		if( chrom[i] == '1' ) ones++;
	return ones;
}

//
// trap function described in Harik's Illigal Report No. 99010
// The global optimum is at 0000 and has fitness k+1.
// The local (deceptive) optima is at 1111 and has fitness k.
//
double trap(char *chrom, int lchrom)
{
	const int TRAP_M = lchrom / TRAP_K;
	double result = 0;
	int startBit , endBit , ones;
	for ( int i = 0; i < TRAP_M; i++ )
	{
		startBit = i * TRAP_K;
		endBit = startBit + TRAP_K - 1;
		ones = unitation( chrom, startBit, endBit );

		if ( ones == TRAP_K )
			result += 1.0 * ones;
		else
			result += (TRAP_K - 1 - ones) * 1.0;
	}
	return result;
}

double onemax(char *chrom , int lchrom)
{
	return unitation(chrom , 0 , lchrom-1);
}

double correctBB(char *chrom , int lchrom , model *M)
{
	return 0.0;
}
//
// Objective function.
// Change this function to try different problems
//
double objective_func( char *chrom, int lchrom )
{

	std::cout << parameter::generation << std::endl;

	switch (parameter::objfunc)
	{
		case ONEMAX:
			return onemax(chrom , lchrom);
		case TRAP:
			return trap(chrom , lchrom);
		default:
			puts("assign an objective function");
			exit(-1);
	}	

}

double objective_func(char *chrom , int lchrom , model* M)
{
	if(parameter::generation < 2)
		return trap(chrom,lchrom);
	else 
		return correctBB(chrom , lchrom , M);
}






