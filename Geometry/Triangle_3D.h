
#ifndef TRIANGLE_3D_H
#define TRIANGLE_3D_H

#include <Geometry/Vector_3D.h>

class Triangle3D
{
public:
	Triangle3D();
	Triangle3D(Vec3D p1, Vec3D p2, Vec3D p3);


public:
	Vec3D m_p1;
	Vec3D m_p2;
	Vec3D m_p3;

private:



};




#endif // TRIANGLE_3D_H
