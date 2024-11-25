
#ifndef VECND_H
#define VECND_H

#include <iostream>

// this looks useful:
// https://stackoverflow.com/questions/499106/what-does-template-unsigned-int-n-mean

template<unsigned int N>
class VecND
{
public:
	float Coordinates[N];

	VecND();
	VecND(float x, float y, float z);

	Vec3D& operator+=(const Vec3D& v);
	Vec3D& operator-=(const Vec3D& v);
	Vec3D& operator*=(float c);
	Vec3D& operator/=(float c);
	float length();
	float lengthSquare();

	static float angle(Vec3D& v1, Vec3D& v2);

	// Philip Nowell normalization (to map vectors onto a sphere): http://mathproofs.blogspot.com/2005/07/mapping-cube-to-sphere.html
	void normalize();
	void PN_normalization();

};

#endif // VECND_H
