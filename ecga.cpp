// -*- c++ -*-
//
//  File:         ecga.cpp
//
//  Description:  C++ implementation of the class ecga.
//                Contains the ECGA loop.
//
//  Author:       Fernando Lobo
//
//  Date:         June/1999
//
//  Modified to be compliant with gcc 3.4 by Kumara Sastry
//  Date:        March/2006

#include <iostream>
#include <iomanip>
#include <fstream>

#include "ecga.hpp"
#include "parameter.hpp"
#include "population.hpp"
#include "mpm.hpp"
#include "utility.hpp"
#include "model.hpp"

extern randomG RANDOM;

//----------------------------------------------------------

void ecga::report( std::ofstream &outfile, population *pop, int gen )
{
  //
  // get information about the best individual in the population
  //
  chromosome bestChrom;
  bestChrom = (*pop)[ pop->best() ];

  //
  // print it
  //
	std::cout << "generation      : " << gen << std::endl
       << "best fitness    : " << pop->maxfit() << std::endl
       << "avg fitness     : " << pop->avgfit() << std::endl
       << "best chromosome : " << bestChrom << std::endl
       << "------------------------------------------------------------"
       << std::endl;
  outfile << "Generation " << gen << std::endl;
  outfile << *pop;
}

bool ecga::done( population *pop, int gen )
{
  switch( parameter::stop_criteria )
   {
     case ALLELE_CONVERGENCE : return sc_allele_conv( *pop, gen );
     case MAX_GENERATIONS    : return sc_maxgen( *pop, gen );
     case FOUND_OPTIMA       : return sc_found_optima(*pop ,gen);
     default: 
        error("This should never happen.");
   }
}

//
// runs the ECGA and sends output information to the 'outfile'.
//
void ecga::run( std::ofstream &outfile )
{
  int gen = 0;

  //
  // first population with random individuals
  //
  population *pop = new population( parameter::popsize );       
  pop->random();  
  pop->evaluate();
  pop->statistics();   
  report( outfile, pop, gen );

  while( !done( pop, gen ) )      
    { 
      gen++;
      //
      // apply selection
      //
      population *temp_pop = new population( pop->popsize() );
      pop->selection( temp_pop );      
      delete pop;     // delete unnecessary temporary
      pop = temp_pop;

      //
      // model the population with a greedy MPM search
      //
      mpm MPM( parameter::lchrom );   
      MPM.model( pop, outfile );  
////////////////// DELETE Below later/////////////////////////
     
	  model *SchemataModel = new model(MPM , pop);

///////////////// You should done here///////////////////////
      
      if( parameter::report_MPM ) std::cout << "MPM: " << MPM << std::endl;

      //
      // generate a new population using the MPM
      //
      temp_pop = new population( pop->popsize() ); 
      MPM.generate( pop, temp_pop );  
      delete pop;
      pop = temp_pop;
      
      //
      // evaluate individuals and do the report
      //
      pop->evaluate();                  
      pop->statistics();                
      report( outfile, pop, gen );
    }

  //
  // cleanup
  //
  delete pop;
}
