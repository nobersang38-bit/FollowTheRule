#include "Vector.h"

Vector operator*(const Vector& A, int B)//이거는 더 멀리가고 싶을때 사용합니다
{
	return Vector(A.Y * B, A.X * B);
}

Vector operator+(const Vector& A, const Vector& B)
{
	return Vector(A.Y + B.Y, A.X + B.X);
}


Vector operator-(const Vector& A, const Vector& B)//방향 구할때 씁시다
{
	return Vector(A.Y - B.Y, A.X - B.X);
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


int Vector::Magnitude()
{
	return X + Y;
}
