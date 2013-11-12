// -*- c++ -*-
//
//  File:         population.hpp
//
//  Description:  C++ interface for the class population.
//
//  Author:       Fernando Lobo
//
//  Date:         June/1999
//
//  Modified to be compliant with gcc 3.4 by Kumara Sastry
//  Date:        March/2006


#ifndef _population_hpp
#define _population_hpp

#include <assert.h>
#include <iostream>
#include <fstream>

#include "chromosome.hpp"
#include "parameter.hpp"

class population
{
  private:
    int        PopSize;             // population size
    chromosome *Chromosomes;        // individuals
    int        *MatingPool;         // mating pool

                                    // information for statistical purposes
    int        Best;                // index of best individual
    double     MaxFit;              // maximum fitness
    double     MinFit;              // minimum fitness
    double     AvgFit;              // average fitness    

    int        tournament_winner( int *shufflearray, int &pick, int s );

  public:
    
    population( int popsize );
    population( population &pop );
    ~population();
    void random();
    void selection( population *newpop );
    void evaluate();   
    void statistics(); 
    int popsize(){ return PopSize; }
    int best() { return Best; }
    double maxfit() { return MaxFit; }
    double minfit() { return MinFit; }
    double avgfit() { return AvgFit; }

    chromosome & operator[]( int index );
    population & operator=( population &pop );
    friend std::ostream &operator<< ( std::ostream &out, population &pop );
    bool converged();
   
    //
    // selection schemes
    // 
    friend void tselect_without_replacement( population &pop );  
    
    //
    // stopping criterias
    //
    friend bool sc_maxgen( population &pop, int gen );
    friend bool sc_allele_conv( population &pop, int gen );
    friend bool sc_found_optima(population &pop , int gen);	
};

#endif
