// -*- c++ -*-
//
//  File:         parameter.hpp
//
//  Description:  definition of parameters for the ECGA.
//
//  Author:       Fernando Lobo
//
//  Date:         June/1999
//
//  Modified to be compliant with gcc 3.4 by Kumara Sastry
//  Date:        March/2006


#ifndef _parameter_hpp
#define _parameter_hpp

enum OBJFUNC {TRAP , ONEMAX};

class model;
class parameter    
{
 public:
  static double seed;              // seed for random number generator
  static int    lchrom;            // chromosome length
  static int    popsize;           // population size
  static double pcross;            // probability of crossover
  static int    tournament_size;   // tournament size
  static int    stop_criteria;     // stopping criteria for the algorithm
  static double stop_criteria_arg; // stop criteria argument (ex: maxgens= x)
  static bool   learn_MPM;         // on = learns linkage, off = compact GA

  static bool   report_pop;
  static bool   report_string;
  static bool   report_fitness;
  static bool   report_MPM;

  static OBJFUNC objfunc;
  static bool found_optima;

  static model *schemata;
  static int generation ;
};


//
// constant definitions for stopping criterias
//
const int ALLELE_CONVERGENCE          = 60;
const int MAX_GENERATIONS             = 61;
const int FOUND_OPTIMA		      = 62;	

//
// constant definitions for trap
//

const int TRAP_K = 5;


#endif



