#pragma once
#include <limits>
#include <thread>

//꼭 생성 합시다
class Tools
{
public:
	//InMin<= Return < InMax
	static int RandomRange(int InMin, int InMax, int Seed = -1);

	static int Clamp(int InValue, int InMin = 0, int InMax = INT_MAX);

	static int Abs(int InValue);

	static bool GetKey(char InKey);

	static float DeletaTime();

	static enum class Direction
	{
		None = 0,
		Up,
		Down,
		Left,
		Right,
		DirectionMax
	};
};

