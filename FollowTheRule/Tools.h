#pragma once
#include <limits>
#include <thread>

//�ʿ��� �������� �־���� Ŭ����
class Tools
{
public:
	//InMin<= Return < InMax
	static int RandomRange(int InMin, int InMax, int Seed = -1);

	static int Clamp(int InValue, int InMin = 0, int InMax = INT_MAX);

	static int Abs(int InValue);

	//�Է¹��� Ű�� ����
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

