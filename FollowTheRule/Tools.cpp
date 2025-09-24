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

int Tools::Clamp(int InValue, int InMin, int InMax)
{
	if (InMin > InMax)
	{
		int Temp = InMin;
		InMin = InMax;
		InMax = Temp;
	}

	if (InValue < InMin)
	{
		InValue = InMin;
	}
	else if (InValue > InMax)
	{
		InValue = InMax;
	}
	return InValue;
}
