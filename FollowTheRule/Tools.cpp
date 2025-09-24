#include "Tools.h"
#include <random>

int Tools::RandomRange(int InMin, int InMax, int Seed)
{
	if (Seed != -1)
	{
		srand(Seed);
	}
	return (rand() % (InMax - InMin)) + InMin;
}
