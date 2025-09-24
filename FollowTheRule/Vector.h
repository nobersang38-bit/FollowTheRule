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

	static inline const Vector Up() { return Vector(0, 1); }
	static inline const Vector Down() { return Vector(0, -1); }
	static inline const Vector Left() { return Vector(-1, 0); }
	static inline const Vector Right() { return Vector(1, 0); }
	static inline const Vector Zero() { return Vector(0, 0); }

	Vector operator*(int Other);//�̰Ŵ� �� �ָ����� ������ ����սô�

	Vector operator+(const Vector& Other);

	Vector operator-(const Vector& Other);//���� ���Ҷ� ���ô�

	Vector& operator*=(int Other);

	Vector& operator+=(const Vector& Other);

	Vector& operator-=(const Vector& Other);

	bool operator==(const Vector& Other);

	bool operator!=(const Vector& Other);
};




//�̰Ŵ� ��Į�� ��� �սô�
//bool operator>(const Vector& A, const Vector& B)
//{
//	return A.
//}