#include <cmath>
#include "generator/sphere.h"

Sphere::Sphere(double radius, int slices, int stacks)
{
    double stackStep = 2 * M_PI / slices; // angle between each slice
    double sliceStep = M_PI / stacks; // angle between each stack

    std::vector<Vertex> grid;

    grid.emplace_back(Point3(0, -radius, 0), Vector3(0, -1, 0));

    // for each stack
    for (int i = 1; i < stacks; i++) {
        double beta = i * sliceStep - M_PI_2f; // angle of current stack
        double y = radius * sin(beta); // height of current stack
        // for each slice
        for (int j = 0; j < slices; j++) {
            double alpha = j * stackStep; // angle of current slice
            double x = radius * cos(beta) * sin(alpha);
            double z = radius * cos(beta) * cos(alpha);
            grid.emplace_back(Point3(x, y, z), Vector3::polar(1, alpha, beta));
        }
    }

    grid.emplace_back(Point3(0, radius, 0), Vector3(0, 1, 0));

    // bottom cone, one triangle per slice
    for (int i = 1; i <= slices; i++) {
        vertices.push_back(grid[0]);
        vertices.push_back(grid[i % slices + 1]);
        vertices.push_back(grid[i]);
    }

    // middle part, two triangles per slice
    for (int i = 1; i < stacks - 1; i++) {
        for (int j = 1; j <= slices; j++) {
            int bottomLeft = (i - 1) * slices + j;
            int bottomRight = (i - 1) * slices + j % slices + 1;
            int topLeft = i * slices + j;
            int topRight = i * slices + j % slices + 1;

            vertices.push_back(grid[bottomLeft]);
            vertices.push_back(grid[bottomRight]);
            vertices.push_back(grid[topLeft]);

            vertices.push_back(grid[topLeft]);
            vertices.push_back(grid[bottomRight]);
            vertices.push_back(grid[topRight]);
        }
    }

    // top cone, one triangle per slice
    int from = (stacks - 2) * slices;
    int to = from + slices + 1;
    for (int i = 1; i <= slices; i++) {
        vertices.push_back(grid[from + i]);
        vertices.push_back(grid[from + i % slices + 1]);
        vertices.push_back(grid[to]);
    }
}
