#pragma once
class Vector
{
public:
	int Y = 0;
	int X = 0;

	Vector(int InX, int InY) : X(InX), Y(InY) {}

	/// <summary>
	/// ������ Magnitude�� ���ϴ� �Լ�(���� ���� �ƴϰ� ���ο� ���θ� �������� ���ϴ� �ִ� �����Դϴ�)(���� 1,1��ġ�� �ִٸ� 2�� Mignitude�� �˴ϴ�)
	/// </summary>
	/// <returns></returns>
	int Magnitude();

	Vector& operator*=(int Other);

	Vector& operator+=(const Vector& Other);

	Vector& operator-=(const Vector& Other);
};

//�̰Ŵ� ��Į�� ��� �սô�
//bool operator>(const Vector& A, const Vector& B)
//{
//	return A.
//}