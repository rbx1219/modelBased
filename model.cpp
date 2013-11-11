#include "model.hpp"

model::model(mpm M , population p)
{	
	bbnum = M.num_subsets();
	pop = p;
	sets = new subset[bbnum];
	for(int i = 0 ; i < bbnum; i++)
		sets[i] = MPM[i]
}

