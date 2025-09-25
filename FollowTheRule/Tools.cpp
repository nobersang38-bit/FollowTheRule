#include <random>
#include "Tools.h"
#include "GameManager.h"

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

int Tools::Abs(int InValue)
{
	return InValue < 0 ? -InValue : InValue;
}

bool Tools::GetKey(char InKey)
{
	if (InKey == GameManager::CurrentInputGameManager())//키를 감지하는 부분
	{
		return true;
	}
	return false;
}

float Tools::DeletaTime()
{
	return GameManager::DeltaTimeGameManager();
}

//float Tools::DeletaTime()
//{
//	return delta.;
//}
