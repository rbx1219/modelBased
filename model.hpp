#include "intlist.hpp"
#include "population.hpp"

class model
{
	public:
		model(int n);
		int getBBnum() {return bbnum;}
		intList * getList() {return BBList;}
		int * getbestSchemata() {return bestSchemata;}
		void calculateSchemataFitness(population *pop);

	private:
		int bbnum;
		intList *BBList;
		int * bestSchemata;
};
