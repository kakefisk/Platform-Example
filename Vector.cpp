#include "Vector.h"
#include <cmath>

Vector::Vector() : x(0), y(0) {}

Vector::Vector(int x, int y) : x(x), y(y) {}

Vector& Vector::operator = (const Vector& other)
{
    if (this == &other)
	{
		return *this;
	}
     
    x = other.x;
    y = other.y;
     
    return *this;
}
     
Vector& Vector::operator += (const Vector& other)
{
    x += other.x;
    y += other.y;
     
    return *this;
}
     
Vector& Vector::operator -= (const Vector& other)
{
    x -= other.x;
    y -= other.y;
     
    return *this;
}
     
Vector& Vector::operator *= (int other)
{
    x *= other;
    y *= other;
     
    return *this;
}
     
//binary operations
     
const Vector Vector::operator + (const Vector other) const
{
        return Vector(*this) += other;
}
     
const Vector Vector::operator - (const Vector other) const
{
    return Vector(*this) -= other;
}
     
const Vector Vector::operator * (int other) const
{
    return Vector(*this) *= other;
}
     
//comparison operations
     
bool Vector::operator == (const Vector& other)
{
    return (x == other.x && y == other.y);
}
     
bool Vector::operator != (const Vector& other)
{
        return !(*this == other);
}
     
int Vector::Length() const
{
        return sqrt(x*x + y*y);
}
     
void Vector::Normalize()
{
    int length = Length();
     
    if (length > 0)
    {
        x /= length;
        y /= length;
    }
}