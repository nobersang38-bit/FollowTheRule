#pragma once
#include <limits>
#include <thread>

//필요한 도구들을 넣어놓은 클래스
class Tools
{
public:
	//InMin<= Return < InMax
	static int RandomRange(int InMin, int InMax, int Seed = -1);

	static int Clamp(int InValue, int InMin = 0, int InMax = INT_MAX);

	static int Abs(int InValue);

	//입력받은 키를 감지
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

