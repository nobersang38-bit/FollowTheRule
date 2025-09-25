#pragma once
#include <limits>
namespace Tools
{
	//InMin<= Return < InMax
	int RandomRange(int InMin, int InMax, int Seed = -1);

	int Clamp(int InValue, int InMin = 0, int InMax = INT_MAX);

	int Abs(int InValue);

	enum class Direction
	{
		None = 0,
		Up,
		Down,
		Left,
		Right,
		DirectionMax
	};
};

