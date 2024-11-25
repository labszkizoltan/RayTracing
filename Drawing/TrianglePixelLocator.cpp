#include "TrianglePixelLocator.h"
#include <algorithm>

std::vector<LocationSpecifier> TrianglePixelLocator::LocatePixels(Vec2D p1, Vec2D p2, Vec2D p3)
{
    auto result = std::vector<LocationSpecifier>();
    float x0 = std::min({ p1.x, p2.x, p3.x });
    float y0 = std::min({ p1.y, p2.y, p3.y });
    float x1 = std::max({ p1.x, p2.x, p3.x });
    float y1 = std::max({ p1.y, p2.y, p3.y });

    Vec2D k1 = p2 - p1, k2 = p3 - p1;
    // Vec2D q1 = Vec2D(k2.y, -k2.x) / (k1.length()*k2.length()), q2 = Vec2D(k1.y, -k1.x) / (k1.length() * k2.length());
    Vec2D q1, q2;
    
    CalculateReciprocVectorSystem(k1, k2, q1, q2);
    float Q11 = k1 * q1, Q12 = k1 * q2, Q21 = k2 * q1, Q22 = k2 * q2;


    for (int y = y0; y < y1; y++)
    {
        for (int x = x0; x < x1; x++)
        {
            Vec2D r = Vec2D(x, y) - p1;
            float lambda1 = r * q1;
            float lambda2 = r * q2;
            if (0 <= lambda1 && 0 <= lambda2 && lambda1 + lambda2 <= 1)
            {
                result.push_back(LocationSpecifier(Vec2D(x, y), lambda1, lambda2));
            }
        }
    }

    return result;
}


void TrianglePixelLocator::CalculateReciprocVectorSystem(Vec2D k1, Vec2D k2, Vec2D& q1, Vec2D& q2)
{
    float K11 = k1 * k1;
    float K12 = k1 * k2;
    float K21 = k2 * k1;
    float K22 = k2 * k2;
    float det = K11 * K22 - K12 * K21;
    if (det == 0)
    {
        std::cout <<  "reciprocal vector system doesnt exist\n";
        return;
    }

    float Q11 = K22 / det;
    float Q12 = -K21 / det;
    float Q21 = -K12 / det;
    float Q22 = K11 / det;

    q1 = Q11 * k1 + Q12 * k2;
    q2 = Q21 * k1 + Q22 * k2;
}


