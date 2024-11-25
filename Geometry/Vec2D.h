
#ifndef VEC2D_H
#define VEC2D_H

#include <iostream>

struct Vec2D
{
	float x, y;
	Vec2D();
	Vec2D(float x, float y);

	Vec2D& operator+=(const Vec2D& v);
	Vec2D& operator-=(const Vec2D& v);
	Vec2D& operator*=(float c);
	Vec2D& operator/=(float c);
	float length();
	float lengthSquare();

	static float angle(Vec2D& v1, Vec2D& v2);
	void normalize();

};


std::ostream& operator<<(std::ostream& stream, const Vec2D& vec);

Vec2D operator+(const Vec2D& v1, const Vec2D& v2);

Vec2D operator-(const Vec2D& v1, const Vec2D& v2);

// Scalar product of vectors
float operator*(const Vec2D& v1, const Vec2D& v2);

// Multiply vector with a scalar
Vec2D operator*(const Vec2D& v1, float c);

// Multiply vector with a scalar, reversed order
Vec2D operator*(float c, const Vec2D& v1);

// Divide vector with a scalar
Vec2D operator/(const Vec2D& v1, float c);

#endif // VEC2D_H
