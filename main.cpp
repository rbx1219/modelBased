// -*- c++ -*-
//
//  File:         main.cpp
//
//  Description:  Contains the main function.
//
//  Author:       Fernando Lobo
//
//  Date:         June/1999
//
//  Modified to be compliant with gcc 3.4 by Kumara Sastry
//  Date:        March/2006


#include "utility.hpp"     // utility functions and procedures
#include "random.hpp"      // random number generator
#include "parameter.hpp"   // parameters for the ECGA
#include "ecga.hpp"        // ECGA code
#include "objfunc.hpp"

#include <assert.h>
#include <iostream>
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

double parameter::seed;
int    parameter::lchrom;
int    parameter::popsize;
double parameter::pcross;
int    parameter::tournament_size;    
int    parameter::stop_criteria;     
double parameter::stop_criteria_arg; 
bool   parameter::learn_MPM;   

bool   parameter::report_pop;
bool   parameter::report_string;
bool   parameter::report_fitness;
bool   parameter::report_MPM;
OBJFUNC parameter::objfunc = TRAP;
bool parameter::found_optima = false;

randomG RANDOM;

// return the identifier of the stop criteria. return -1 if not found.
int find_stop_criteria( char *s )
{
  if( strcmp( s, "allele_convergence" ) == 0 ) return ALLELE_CONVERGENCE;
  if( strcmp( s, "max_generations" ) == 0 ) return MAX_GENERATIONS;
  if( strcmp( s, "found_optima") == 0) return FOUND_OPTIMA;
  return -1;
}


// 
// read parameters from input file.
// 
void read_parameters( std::ifstream &in )
{
  const int unset = -1;
  int op;
  char  s[100] = "";
  char  s2[100] = "";

  while( strcmp( s, "BEGIN" ) != 0 ) 
    {
      in.getline( s, 100 );
      std::cout << s << std::endl;
    }

  in >> s >> parameter::lchrom;
  std::cout << s << "   " << parameter::lchrom << std::endl; 
  errorcheck("Check lchrom.", parameter::lchrom > 0 );

  in >> s >> parameter::seed;
  std::cout << s << "   "  << parameter::seed << std::endl;
  errorcheck("seed must be in 0..1", parameter::seed > 0 && parameter::seed < 1 );

  in >> s >> parameter::popsize;
  std::cout << s << "   "  << parameter::popsize << std::endl;
  errorcheck("population size must be even.", parameter::popsize % 2 == 0 );
  errorcheck("population size must be positive.", parameter::popsize > 0 );

  in >> s >> parameter::pcross;
  std::cout << s << "   "  << parameter::pcross << std::endl;
  errorcheck("pcross must be in 0..1", parameter::pcross >= 0 && parameter::pcross <= 1 );

  in >> s >> parameter::tournament_size;
  std::cout << s << "   "  << parameter::tournament_size << std::endl;

  in >> s >> s2; parameter::learn_MPM        = (strcmp(s2,"on") == 0);
  std::cout << s << "   "  << s2 << std::endl;

  in >> s >> s2; op = find_stop_criteria( s2 );
  std::cout << s << "   "  << s2 << std::endl;
  parameter::stop_criteria = op;
  errorcheck("stop criteria not available.", op != -1 );

  in >> s >> parameter::stop_criteria_arg;
  std::cout << s << "   "  << parameter::stop_criteria_arg << std::endl;

  in.getline( s, 100 );

  in.getline( s, 100 );
  in.getline( s, 100 );
  in.getline( s, 100 );

  in >> s >> s2;
  parameter::report_pop = (strcmp(s2,"on") == 0); 
  std::cout << s << "   "  << s2 << std::endl;
  in >> s >> s2;
  parameter::report_string = (strcmp(s2,"on") == 0);
  std::cout << s << "   "  << s2 << std::endl;
  in >> s >> s2; 
  parameter::report_fitness = (strcmp(s2,"on") == 0);
  std::cout << s << "   "  << s2 << std::endl;
  in >> s >> s2;
  parameter::report_MPM = (strcmp(s2,"on") == 0);
  std::cout << s << "   "  << s2 << std::endl;

  std::cout << "--------------------------------------------------------------------" << std::endl;
	

} // end of read_parameters


int main( int argc, char *argv[] )
{
  // process command line
  if( argc != 3 )   
    {
      std::cout << "Usage: " << argv[0] << " inputfile outputfile" << std::endl;
      std::cout << "       Please read the README file." << std::endl;
      exit(1);
    }
  
  // read parameters from input file
  std::ifstream infile( argv[1] ); 
  read_parameters( infile );
  infile.close();

  // open output file
  std::ofstream outfile( argv[2] );  

  // initilalize random number generator
  RANDOM.randomize( parameter::seed );

  // run the ECGA algorithm
  ecga ECGA;
  ECGA.run( outfile );
  std::cout << "ECGA done" << std::endl;

  outfile.close();
  return 1;
}

