#include "model.hpp"
#include <string.h>
model::model(mpm *M , population *p)
{	
	bbnum = M->num_subsets();
	pop = new population(*p);
	sets = new subset[bbnum];
	BestSchemata = new int[bbnum];
	for(int i = 0 ; i < bbnum; i++)
		sets[i] = (*M)[i];
}

void model::calculateSchemata()
{
	int i;
	for(i = 0 ; i < bbnum ; i++)
	{
		int maxfit = 0;
		for(int j = 0 ; j < sets[i].numCounts() ; j++)	
			if(sets[i].fit[j] / sets[i].counts[j] > maxfit)
			{
				maxfit = sets[i].fit[j] / sets[i].counts[j];
				BestSchemata[i] = j;
			}
	}
	return ;
}

model::~model()
{
	delete pop;
	delete sets;
}
