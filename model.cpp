#include "model.hpp"

model::model(mpm M , population *p)
{	
	bbnum = M.num_subsets();
	pop = new population(*p);
	sets = new subset[bbnum];
	for(int i = 0 ; i < bbnum; i++)
		sets[i] = M[i];
}

void model::calculateSchemata()
{
	int i;
	for(i = 0 ; i < bbnum ; i++)
	{
		printf("%d\n" , sets[i].size())	;	
	}
	return ;
}

model::~model()
{
	delete pop;
	delete sets;
}
