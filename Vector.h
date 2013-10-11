#ifndef VECTOR_H
#define VECTOR_H

class Vector
{
	public:
    int x, y;

	Vector();
	Vector(int x, int y);

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
     
	int Length() const;
	void Normalize();
};

#endif