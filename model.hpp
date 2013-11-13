#ifndef model_H
#define model_H

#include "mpm.hpp"
#include "population.hpp"
#include "subset.hpp"

class model
{
	public:
		model & operator=(model &s);
		model();
		model(mpm *M , population *p);
		~model();
		int * getBestSchemata()	{return BestSchemata;}
		void calculateSchemata();
		int get_bbnum() { return bbnum; }
		subset *sets;		
	private:
		int bbnum;
		int * BestSchemata;
		population *pop;
};

#endif
