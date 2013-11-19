#include "chromosome.hpp"
#include <iostream>


int main()
{
	int length = 40;
	char *tmp = new char[length];
        chromosome *tar = new chromosome(length);
	for(int i = 0 ; i < length ; i++)
		 tmp[i] = '1';
	
	delete[] tmp;
	return 0;
}

