#pragma once
class Vector
{
public:
	int Y = 0;
	int X = 0;

	Vector(int InX, int InY) : X(InX), Y(InY) {}

	/// <summary>
	/// 벡터의 Magnitude를 구하는 함수(직선 방향 아니고 세로와 가로만 움직여서 구하는 최단 길이입니다)(만약 1,1위치에 있다면 2가 Mignitude가 됩니다)
	/// </summary>
	/// <returns></returns>
	int Magnitude();

	Vector& operator*=(int Other);

	Vector& operator+=(const Vector& Other);

	Vector& operator-=(const Vector& Other);
};

//이거는 스칼라만 계산 합시다
//bool operator>(const Vector& A, const Vector& B)
//{
//	return A.
//}