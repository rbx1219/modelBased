#include "model.hpp"
#include "population.hpp"

model::model(int n)
{
	bbnum = n;
	BBList = new intList[bbnum];
	bestSchemata = new int[bbnum];

}

void model::calculateSchemataFitness(population *pop)	
{
	int i ;
	for(int i = 0 ; i < bbnum ; i++)
	{
		int allocate = BBList[i].length();
		int schemataspace = 1;
		for(int j = 0 ; j < allocate ; j++)
			schemataspace *= 2;
		int *count = new int[allocate];
		float *fitness = new float[allocate];
		int *mannual = new int[schemataspace];
		int index = 0;

		//initial array
		for(int j = 0 ; j < allocate ; j++)
		{
			count[j] = 0;
			mannual[j] = 0;
			fitness[j] = 0.0;
		}

		for(int j = 0 ; j < pop->popsize() ; j++)
		{
			int tmp = 0;
			bool isFound = false;
			for(int k = 0 ; k < BBList[i].length(); k++)
				tmp = tmp*2 + *pop[j][BBList[i][k]].allele();

			for(int k = 0 ; k < index ; k++)
				if(mannual[k] == tmp)
				{
					isFound = true;
					fitness[k] += (*pop)[j].fitness();
					count[k]++;
				}
			if(!isFound)
			{
				int in = index;
				mannual[in] = tmp;
				fitness[in] = (*pop)[j].fitness();
				count[in]++;
				index++;
			}
		}
		delete[] count;
		delete[] fitness;
		delete[] mannual;
	}
}
