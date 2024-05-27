#include <cmath>
#include "generator/models/box.h"

using std::pair, std::vector;

Box::Box(double size, int divisions)
{
    static vector<Vector3> normals = {
            {0,  -1, 0},
            {0,  0,  1},
            {1,  0,  0},
            {0,  0,  -1},
            {-1, 0,  0},
            {0,  1,  0},
    };

    double halfSize = size / 2.0;

    vector<Point3> startingPoints = {
            {-halfSize, -halfSize, halfSize},
            {-halfSize, -halfSize, halfSize},
            {halfSize,  -halfSize, halfSize},
            {halfSize,  -halfSize, -halfSize},
            {-halfSize, -halfSize, -halfSize},
            {-halfSize, halfSize,  -halfSize}
    };

    double divSize = size / divisions;

    vector<pair<Vector3, Vector3>> dirs = {
            {{0,        0, -divSize}, {divSize, 0,       0}},
            {{divSize,  0, 0},        {0,       divSize, 0}},
            {{0,        0, -divSize}, {0,       divSize, 0}},
            {{-divSize, 0, 0},        {0,       divSize, 0}},
            {{0,        0, divSize},  {0,       divSize, 0}},
            {{0,        0, divSize},  {divSize, 0,       0}}
    };

    vector<Vertex> grid;

    for (int i = 0; i < 6; i++) {
        for (int j = 0; j <= divisions; j++) {
            for (int k = 0; k <= divisions; k++) {
                Point3 p = startingPoints[i] + dirs[i].first * k + dirs[i].second * j;
                grid.emplace_back(p, normals[i], Vector2((double) k / divisions, (double) j / divisions));
            }
        }
    }

    for (int i = 0; i < 6; i++) {
        int sideIndex = i * (divisions + 1) * (divisions + 1);
        for (int j = 0; j < divisions; j++) {
            for (int k = 0; k < divisions; k++) {
                int bottomLeft = sideIndex + j * (divisions + 1) + k;
                int bottomRight = bottomLeft + 1;
                int topLeft = bottomLeft + divisions + 1;
                int topRight = topLeft + 1;

                vertices.push_back(grid[bottomLeft]);
                vertices.push_back(grid[bottomRight]);
                vertices.push_back(grid[topRight]);

                vertices.push_back(grid[topLeft]);
                vertices.push_back(grid[bottomLeft]);
                vertices.push_back(grid[topRight]);
            }
        }
    }
}
