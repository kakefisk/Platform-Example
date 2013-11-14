#ifndef VECTOR_H
#define VECTOR_H

template <class T>
class Vector
{
	public:
    T x, y;

	Vector();
	Vector(T x, T y);

	Vector& operator = (const Vector& other);
	Vector& operator += (const Vector& other);
	Vector& operator -= (const Vector& other);
	Vector& operator *= (int other);
     
	//binary operations
	const Vector operator + (const Vector other) const;
	const Vector operator - (const Vector other) const;
	const Vector operator * (int other) const;
     
	//comparison operations
	bool operator == (const Vector& other);
	bool operator != (const Vector& other);
     
	T Length() const;
	void Normalize();
};

#include "Vector.inl"

typedef Vector<int> VectorI;
typedef Vector<float> VectorF;

#endif