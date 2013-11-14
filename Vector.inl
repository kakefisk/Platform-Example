#include "Vector.h"
#include <cmath>

template<typename T>
inline Vector<T>::Vector() : x(0), y(0) {}

template<typename T>
inline Vector<T>::Vector(T x, T y) : x(x), y(y) {}

template<typename T>
inline Vector<T>& Vector<T>::operator = (const Vector<T>& other)
{
    if (this == &other)
	{
		return *this;
	}
     
    x = other.x;
    y = other.y;
     
    return *this;
}
     
template<typename T>
inline Vector<T>& Vector<T>::operator += (const Vector<T>& other)
{
    x += other.x;
    y += other.y;
     
    return *this;
}
     
template<typename T>
inline Vector<T>& Vector<T>::operator -= (const Vector<T>& other)
{
    x -= other.x;
    y -= other.y;
     
    return *this;
}
     
template<typename T>
inline Vector<T>& Vector<T>::operator *= (int other)
{
    x *= other;
    y *= other;
     
    return *this;
}
     
//binary operations
     
template<typename T>
inline const Vector<T> Vector<T>::operator + (const Vector<T> other) const
{
        return Vector<T>(*this) += other;
}
     
template<typename T>
inline const Vector<T> Vector<T>::operator - (const Vector<T> other) const
{
    return Vector<T>(*this) -= other;
}
     
template<typename T>
inline const Vector<T> Vector<T>::operator * (int other) const
{
    return Vector<T>(*this) *= other;
}
     
//comparison operations
     
template<typename T>
inline bool Vector<T>::operator == (const Vector<T>& other)
{
    return (x == other.x && y == other.y);
}
     
template<typename T>
inline bool Vector<T>::operator != (const Vector<T>& other)
{
        return !(*this == other);
}
     
template<typename T>
inline T Vector<T>::Length() const
{
        return sqrt(x*x + y*y);
}
     
template<typename T>
inline void Vector<T>::Normalize()
{
    int length = Length();
     
    if (length > 0)
    {
        x /= length;
        y /= length;
    }
}