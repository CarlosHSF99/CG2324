#include <iostream>
#include "generator/plane.h"

Plane::Plane(float size, int divisions)
{
    float originOffset = size / 2;
    float divisionSize = size / (float) divisions;

    for (int i = 0; i < divisions; i++) {
        for (int j = 0; j < divisions; j++) {
            // back left corner of the current square
            float x1 = (float) i * divisionSize - originOffset;
            float z1 = (float) j * divisionSize - originOffset;

            // front right corner of the current square
            float x2 = x1 + divisionSize;
            float z2 = z1 + divisionSize;

            // first (back right) triangle
            vertices.emplace_back(x1, 0, z1);
            vertices.emplace_back(x2, 0, z2);
            vertices.emplace_back(x2, 0, z1);

            // second (front left) triangle
            vertices.emplace_back(x1, 0, z1);
            vertices.emplace_back(x1, 0, z2);
            vertices.emplace_back(x2, 0, z2);
        }
    }
}
