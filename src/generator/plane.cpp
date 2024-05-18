#include "generator/plane.h"

Plane::Plane(double size, int divisions)
{
    double originOffset = size / 2;
    double divisionSize = size / divisions;

    std::vector<Vertex> grid;
    for (int i = 0; i <= divisions; i++) {
        for (int j = 0; j <= divisions; j++) {
            Point3 p(j * divisionSize - originOffset, 0, i * divisionSize - originOffset);
            Vector3 n(0, 1, 0);
            grid.emplace_back(p, n);
        }
    }

    for (int i = 0; i < divisions; i++) {
        for (int j = 0; j < divisions; j++) {
            // first (back right) triangle
            vertices.push_back(grid[i * (divisions + 1) + j]);
            vertices.push_back(grid[(i + 1) * (divisions + 1) + j + 1]);
            vertices.push_back(grid[i * (divisions + 1) + j + 1]);
            // second (front left) triangle
            vertices.push_back(grid[i * (divisions + 1) + j]);
            vertices.push_back(grid[(i + 1) * (divisions + 1) + j]);
            vertices.push_back(grid[(i + 1) * (divisions + 1) + j + 1]);
        }
    }
}
