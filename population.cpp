// -*- c++ -*-
//
//  File:         population.cpp
//
//  Description:  C++ implementation for the class population.
//
//  Author:       Fernando Lobo
//
//  Date:         June/1999
//
//  Modified to be compliant with gcc 3.4 by Kumara Sastry
//  Date:        March/2006


#include <iostream>
#include <iomanip>
#include <string.h>
#include <math.h>
#include <assert.h>

#include "population.hpp"
#include "gene.hpp"
#include "chromosome.hpp"
#include "random.hpp"
#include "parameter.hpp"
#include "utility.hpp"   

extern randomG RANDOM;

// constructor
population::population( int popsize )
{ 
  PopSize = popsize;
  Chromosomes = new chromosome[ PopSize ];    // allocate memory
  MatingPool = new int[ PopSize ];  
};
 
// copy constructor
population::population( population &pop )
{
  PopSize = pop.PopSize;
  Chromosomes = new chromosome[ PopSize ]; // allocate memory
  MatingPool = new int[ PopSize ];         // for pointer members

  for( int i=0; i< PopSize; i++ )       // copy data of pointer members
   {
     Chromosomes[i] = pop.Chromosomes[i];
     MatingPool[i] = pop.MatingPool[i];
   }
}

// assignment operator
population & population::operator=( population &pop )
{
  if (this == &pop)
    return *this; 

  delete [] Chromosomes;              // deallocates the old population
  delete [] MatingPool;
  
  PopSize = pop.PopSize;
  Chromosomes = new chromosome[ PopSize ];    // make room for the new one
  MatingPool = new int[ PopSize ];

  for( int i=0; i< PopSize; i++ )       // copy data of pointer members
   {
     Chromosomes[i] = pop.Chromosomes[i];
     MatingPool[i] = pop.MatingPool[i];
   }

  return *this;
}

// destructor
population::~population()
{ 
  delete [] Chromosomes; 
  delete [] MatingPool; 
};

// create a population with random individuals.
void population::random()
{
  for( int i=0; i< PopSize; i++ )
    Chromosomes[i].random();
}
  
// index operator
chromosome & population::operator[](int index)
{
  assert( index>=0 && index<PopSize );
  return Chromosomes[index];
}

// print a population
std::ostream &operator<< (std::ostream &out, population &pop)
{
  if( parameter::report_pop )     // print the population
    {
      if( parameter::report_string ) out << std::setw(parameter::lchrom)<< "string";
      if( parameter::report_fitness ) out << std::setw(10) << "fit";
      out << std::endl;
      for( int i=0; i< pop.popsize(); i++ )
	out << pop[i] << std::endl;
   }
  
  out << std::setprecision(7);
  out << "Max fitness     : " << pop.maxfit() << std::endl;
  out << "Avg fitness     : " << pop.avgfit() << std::endl;
  out << "Best chromosome : " << pop[ pop.best() ] << std::endl;
  out << "-------------------------------------------------------" << std::endl;

  return out;
}

//
//  create a new population through selection.
//  the caller should allocate memory for 'newpop'
//
void population::selection( population *newpop )
{
  tselect_without_replacement( *this );               

  // copy individuals from the mating pool into 'newpop'
  for( int i=0; i< PopSize; i++ )
    (*newpop)[i] = Chromosomes[ MatingPool[i] ];
}


// 
//  evaluate objective function values of population members
//
void population::evaluate()
{
  for( int i=0; i< PopSize; i++ )
    Chromosomes[i].evaluate();
}


// compute statistics
void population::statistics()
{
  double fit = Chromosomes[0].fitness();
  double sumfit = fit;
  MaxFit = MinFit = fit;
  Best = 0;

  for( int i=1; i< PopSize; i++ )
    {
      fit = Chromosomes[i].fitness();
      if( fit > MaxFit ) { MaxFit = fit; Best = i; }
      if( fit < MinFit ) MinFit = fit;
      sumfit += fit;
    }

  AvgFit = sumfit / PopSize;
} 



//-------- selection schemes ----------------------------------------
// tournament selection without replacement

// set things up for tournament selection without replacement
void pre_tselect_without_replacement( int *array, int &pick, int popsize )
{
  pick = 0;
  makeshuffle( array, popsize );
}

// tournament selection without replacement
int population::tournament_winner( int *shuffle, int &pick, int tournsize )
{
  int winner = shuffle[pick];
  for( int i=pick+1; i< pick+tournsize; i++ )
    if( Chromosomes[ shuffle[i] ].fitness() > Chromosomes[ winner ].fitness() )
      winner = shuffle[i];
  pick += tournsize;
  return winner;
}

// tournament selection without replacement
// the individuals that survive reproduction are placed in the mating pool
void tselect_without_replacement( population &pop )
{
  int *shuffle = new int [pop.popsize()];
  int pick;
  int s = parameter::tournament_size;

  pre_tselect_without_replacement( shuffle, pick, pop.popsize() );
  for( int i=0; i< pop.popsize(); i++ )
    {
      if( pick+s > pop.popsize() )
	pre_tselect_without_replacement( shuffle, pick, pop.popsize() );
      pop.MatingPool[i] = pop.tournament_winner( shuffle, pick, s );
    }
  delete [] shuffle;
}

//-------- stopping criterias ----------------------------------------

//
// true if all the individuals have the same alleles
//
bool population::converged()
{
  for( int loci=0; loci< parameter::lchrom; loci++ )
    {
      gene g = Chromosomes[0][loci];
      for( int i=1; i< PopSize; i++ )
	if( Chromosomes[i][loci] != g ) return false;
    }
  return true;
}

// true if maxgen = gen
bool sc_maxgen( population &pop, int gen )
{
  return gen == parameter::stop_criteria_arg;
}


// assumes binary coding.
bool sc_allele_conv( population &pop, int dummy )
{
  return pop.converged();
}

bool sc_found_optima(population &pop, int gen)
{
    if(parameter::objfunc == TRAP)
    {
        if(pop.maxfit() - 1e-6 < pop.avgfit())
            return true;
        if(parameter::lchrom * 1.0  == pop.maxfit())
        {
            parameter::found_optima = true;
            return true;
        }

    }
    if(parameter::objfunc == ONEMAX)
    {
        if(pop.maxfit() - 1e-6 < pop.avgfit())
            return true;
        if(parameter::lchrom * 1.0  == pop.maxfit())
        {
            parameter::found_optima = true;
            return true;
        }
    }
}

