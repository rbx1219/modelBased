// -*- c++ -*-
//
//  File:         ecga.hpp
//
//  Description:  C++ interface for the ecga class.
//
//  Author:       Fernando Lobo
//
//  Date:         June/1999
//
//  Modified to be compliant with gcc 3.4 by Kumara Sastry
//  Date:        March/2006

#ifndef _ecga_hpp
#define _ecga_hpp

#include <iostream>
#include <fstream>
#include "population.hpp"
#include "chromosome.hpp"


class ecga
{
  private:
    void report( std::ofstream &outfile, population *pop, int gen );
    bool done( population *pop, int gen );

  public:
    ecga() {}
    ~ecga() {}
    void run( std::ofstream &outfile );
    chromosome best ;	
};

#endif



