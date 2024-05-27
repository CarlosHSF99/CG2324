#include "generator/models/plane.h"

Plane::Plane(double size, int divisions)
{
    double originOffset = size / 2;
    double divisionSize = size / divisions;

    std::vector<Vertex> grid;
    for (int i = 0; i <= divisions; i++) {
        for (int j = 0; j <= divisions; j++) {
            Point3 p(j * divisionSize - originOffset, 0, -i * divisionSize + originOffset);
            Vector3 n(0, 1, 0);
            Vector2 t((double) j / divisions, (double) i / divisions);
            grid.emplace_back(p, n, t);
        }
    }

    for (int i = 0; i < divisions; i++) {
        for (int j = 0; j < divisions; j++) {
            int bottomLeft = i * (divisions + 1) + j;
            int bottomRight = bottomLeft + 1;
            int topLeft = bottomLeft + divisions + 1;
            int topRight = topLeft + 1;

            // first (back right) triangle
            vertices.push_back(grid[bottomLeft]);
            vertices.push_back(grid[bottomRight]);
            vertices.push_back(grid[topLeft]);
            // second (front left) triangle
            vertices.push_back(grid[topLeft]);
            vertices.push_back(grid[bottomRight]);
            vertices.push_back(grid[topRight]);
        }
    }
}
