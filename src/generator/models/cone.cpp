#include <cmath>
#include "generator/models/cone.h"

Cone::Cone(double radius, double height, int slices, int stacks)
{
    double stackStep = 2 * M_PI / slices; // angle between each slice
    double sliceStep = height / stacks; // height between each stack

    std::vector<Vertex> grid;

    for (int i = 0; i <= slices; i++) {
        grid.emplace_back(Point3(0, 0, 0), Vector3(0, -1, 0), Vector2((double) i / slices, 0));
    }

    for (int i = 0; i <= slices; i++) {
        double alpha = i * stackStep; // current angle
        double x = radius * sin(alpha);
        double z = radius * cos(alpha);
        grid.emplace_back(Point3(x, 0, z), Vector3(0, -1, 0), Vector2((double) i / slices, 1));
    }

    double beta = atan2(radius, height);

    for (int i = 0; i < stacks; i++) {
        double stackRadius = (stacks - i) * radius / stacks; // current radius
        double y = i * sliceStep; // current height
        double texY = (double) i / stacks;
        for (int j = 0; j <= slices; j++) {
            double alpha = j * stackStep; // current angle
            double x = stackRadius * sin(alpha);
            double z = stackRadius * cos(alpha);
            double texX = (double) j / slices;
            grid.emplace_back(Point3(x, y, z), Vector3::polar(1, alpha, beta), Vector2(texX, texY));
        }
    }

    for (int i = 0; i <= slices; i++) {
        double alpha = (i - 0.5) * stackStep; // current angle
        grid.emplace_back(Point3(0, height, 0), Vector3::polar(1, alpha, beta), Vector2((double) i / stacks, 1));
    }

    int top = (slices + 1) * (stacks + 1);

    for (int i = 0; i < slices; i++) {
        vertices.push_back(grid[i + 1]);
        vertices.push_back(grid[i + slices + 2]);
        vertices.push_back(grid[i + slices + 1]);

        vertices.push_back(grid[top + i]);
        vertices.push_back(grid[top + i + 1]);
        vertices.push_back(grid[top + i + slices + 2]);
    }

    for (int i = 1; i < stacks; i++) {
        for (int j = 0; j < slices; j++) {
            int bottomLeft = (i + 1) * (slices + 1) + j;
            int bottomRight = (i + 1) * (slices + 1) + j + 1;
            int topLeft = (i + 2) * (slices + 1) + j;
            int topRight = (i + 2) * (slices + 1) + j + 1;

            vertices.push_back(grid[bottomLeft]);
            vertices.push_back(grid[bottomRight]);
            vertices.push_back(grid[topLeft]);

            vertices.push_back(grid[topLeft]);
            vertices.push_back(grid[bottomRight]);
            vertices.push_back(grid[topRight]);
        }
    }
}
