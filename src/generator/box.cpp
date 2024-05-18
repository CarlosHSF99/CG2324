#include <cmath>
#include "generator/box.h"

using std::vector;

Box::Box(double size, int divisions)
{
    auto nd = (float) divisions;
    Point3 startingPoint(-size / 2.f, -size / 2.f, -size / 2.f);

    Vector3 nBase(0, -1, 0);
    Vector3 nTop(0, 1, 0);
    Vector3 nRight(0, 0, -1);
    Vector3 nLeft(0, 0, 1);
    Vector3 nBack(-1, 0, 0);
    Vector3 nFront(1, 0, 0);

    for (int i = 0; i < divisions; i++) {
        for (int j = 0; j < divisions; j++) {
            Vector3 i1 = Vector3(j, i, 0) * (1 / nd);
            Vector3 i2 = Vector3(j, i + 1, 0) * (1 / nd);
            Vector3 i3 = Vector3(j + 1, i, 0) * (1 / nd);
            Vector3 i4 = Vector3(j + 1, i + 1, 0) * (1 / nd);

            // Base triangles
            Point3 p1 = startingPoint + Vector3(i1.x, 0, i1.y) * size;
            Point3 p2 = startingPoint + Vector3(i2.x, 0, i2.y) * size;
            Point3 p3 = startingPoint + Vector3(i3.x, 0, i3.y) * size;
            Point3 p4 = startingPoint + Vector3(i4.x, 0, i4.y) * size;

            vertices.emplace_back(p3, nBase);
            vertices.emplace_back(p2, nBase);
            vertices.emplace_back(p1, nBase);

            vertices.emplace_back(p3, nBase);
            vertices.emplace_back(p4, nBase);
            vertices.emplace_back(p2, nBase);

            // Top triangles
            p1.y = (float) size / 2;
            p2.y = (float) size / 2;
            p3.y = (float) size / 2;
            p4.y = (float) size / 2;

            vertices.emplace_back(p1, nTop);
            vertices.emplace_back(p2, nTop);
            vertices.emplace_back(p3, nTop);

            vertices.emplace_back(p2, nTop);
            vertices.emplace_back(p4, nTop);
            vertices.emplace_back(p3, nTop);

            // Right triangles
            p1 = startingPoint + Vector3(i1.x, i1.y, 0) * size;
            p2 = startingPoint + Vector3(i2.x, i2.y, 0) * size;
            p3 = startingPoint + Vector3(i3.x, i3.y, 0) * size;
            p4 = startingPoint + Vector3(i4.x, i4.y, 0) * size;

            vertices.emplace_back(p1, nRight);
            vertices.emplace_back(p2, nRight);
            vertices.emplace_back(p3, nRight);

            vertices.emplace_back(p2, nRight);
            vertices.emplace_back(p4, nRight);
            vertices.emplace_back(p3, nRight);

            // Left triangles
            p1.z = (float) size / 2;
            p2.z = (float) size / 2;
            p3.z = (float) size / 2;
            p4.z = (float) size / 2;

            vertices.emplace_back(p3, nLeft);
            vertices.emplace_back(p2, nLeft);
            vertices.emplace_back(p1, nLeft);

            vertices.emplace_back(p3, nLeft);
            vertices.emplace_back(p4, nLeft);
            vertices.emplace_back(p2, nLeft);

            // Back triangles
            p1 = startingPoint + Vector3(0, i1.x, i1.y) * size;
            p2 = startingPoint + Vector3(0, i2.x, i2.y) * size;
            p3 = startingPoint + Vector3(0, i3.x, i3.y) * size;
            p4 = startingPoint + Vector3(0, i4.x, i4.y) * size;

            vertices.emplace_back(p3, nBack);
            vertices.emplace_back(p1, nBack);
            vertices.emplace_back(p2, nBack);

            vertices.emplace_back(p3, nBack);
            vertices.emplace_back(p2, nBack);
            vertices.emplace_back(p4, nBack);

            // Front triangles
            p1.x = (float) size / 2;
            p2.x = (float) size / 2;
            p3.x = (float) size / 2;
            p4.x = (float) size / 2;

            vertices.emplace_back(p1, nFront);
            vertices.emplace_back(p3, nFront);
            vertices.emplace_back(p2, nFront);

            vertices.emplace_back(p2, nFront);
            vertices.emplace_back(p3, nFront);
            vertices.emplace_back(p4, nFront);
        }
    }
}
