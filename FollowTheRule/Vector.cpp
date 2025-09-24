#include "Vector.h"
Vector Vector::operator*(int Other)//�̰Ŵ� �� �ָ����� ������ ����սô�
{
	return Vector(X * Other, Y * Other);
}

Vector Vector::operator+(const Vector& Other)
{
	return Vector(X + Other.X, Y + Other.Y);
}


Vector Vector::operator-(const Vector& Other)//���� ���Ҷ� ���ô�
{
	return Vector(X - Other.X, Y - Other.Y);
}

Vector& Vector::operator*=(int Other)
{
	Y *= Other;
	X *= Other;
	return *this;
}

Vector& Vector::operator+=(const Vector& Other)
{
	Y += Other.Y;
	X += Other.X;
	return *this;
}

Vector& Vector::operator-=(const Vector& Other)
{
	Y -= Other.Y;
	X -= Other.X;
	return *this;
}

bool Vector::operator==(const Vector& Other)
{
	return X == Other.X && Y == Other.Y;
}

bool Vector::operator!=(const Vector& Other)
{
	return !(*this == Other);
}

int Vector::Magnitude()
{
	return X + Y;
}
