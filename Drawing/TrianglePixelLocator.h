
#ifndef TRIANGLE_PIXEL_LOCATOR_H
#define TRIANGLE_PIXEL_LOCATOR_H

#include <iostream>
#include <Geometry/Vec2D.h>
#include <ImageHandling/ImageData.h>

struct LocationSpecifier
{
	Vec2D position;
	float lambda1;
	float lambda2;

	LocationSpecifier(Vec2D _position, float _lambda1, float _lambda2)
		: position(_position), lambda1(_lambda1), lambda2(_lambda2) {}

};

class TrianglePixelLocator
{
public:
	static std::vector<LocationSpecifier> LocatePixels(Vec2D p1, Vec2D p2, Vec2D p3);

	static void CalculateReciprocVectorSystem(Vec2D k1, Vec2D k2, Vec2D& q1, Vec2D& q2);


};




#endif // TRIANGLE_PIXEL_LOCATOR_H
