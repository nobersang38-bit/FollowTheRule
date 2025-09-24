#include "Vector.h"
Vector Vector::operator*(int Other)//이거는 더 멀리가고 싶을때 사용합시다
{
	return Vector(X * Other, Y * Other);
}

Vector Vector::operator+(const Vector& Other)
{
	return Vector(X + Other.X, Y + Other.Y);
}


Vector Vector::operator-(const Vector& Other)//방향 구할때 씁시다
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
