#include "mpm.hpp"
#include "population.hpp"
#include "subset.hpp"

class model
{
	public:
		model(mpm M , population *p);
		~model();
		int * getBestSchemata()	{return BestSchemata;}
		void calculateSchemata();
	private:
		int bbnum;
		int * BestSchemata;
		subset *sets;
		population *pop;
};
