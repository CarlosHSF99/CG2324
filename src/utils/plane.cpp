#include <iostream>
#include "utils/plane.h"

Plane::Plane(float size, int divisions)
{
    float originOffset = size / 2;
    float divisionSize = size / (float) divisions;

    for (int i = 0; i < divisions; i++) {
        for (int j = 0; j < divisions; j++) {
            float x = (float) i * divisionSize - originOffset;
            float z = (float) j * divisionSize - originOffset;

            vertices.emplace_back(x, 0, z);
            vertices.emplace_back(x, 0, z + divisionSize);
            vertices.emplace_back(x + divisionSize, 0, z);

            vertices.emplace_back(x + divisionSize, 0, z);
            vertices.emplace_back(x, 0, z + divisionSize);
            vertices.emplace_back(x + divisionSize, 0, z + divisionSize);
        }
    }
}
