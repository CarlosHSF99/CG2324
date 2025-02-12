#include <cmath>
#include <IL/il.h>
#include "generator/models/sphere.h"

Sphere::Sphere(double radius, int slices, int stacks)
{
    double stackStep = 2 * M_PI / slices; // angle between each slice
    double sliceStep = M_PI / stacks; // angle between each stack

    std::vector<Vertex> grid;

    // for each stack
    for (int i = 0; i <= stacks; i++) {
        double beta = i * sliceStep - M_PI_2f; // angle of current stack
        double texY = (double) i / stacks;
        // for each slice
        for (int j = 0; j <= slices; j++) {
            double alpha = j * stackStep; // angle of current slice
            double texX = (double) j / slices;
            Point3 p = Point3::polar(radius, alpha, beta);
            grid.emplace_back(p, Vector3(p).normalize(), Vector2(texX, texY));
        }
    }

    buildSphere(slices, stacks, grid);
}

Sphere::Sphere(double radius, int slices, int stacks, const std::string &heightMap, double heightScale)
{
    ilInit();

    ILuint t;
    ilGenImages(1, &t);
    ilBindImage(t);
    ilLoadImage((ILstring) heightMap.c_str());
    ilConvertImage(IL_LUMINANCE, IL_UNSIGNED_BYTE);
    ILint tw = ilGetInteger(IL_IMAGE_WIDTH);
    ILint th = ilGetInteger(IL_IMAGE_HEIGHT);
    ILubyte *imageData = ilGetData();

    double ratioW = (double) tw / slices;
    double ratioH = (double) th / stacks;

    double stackStep = 2 * M_PI / slices; // angle between each slice
    double sliceStep = M_PI / stacks; // angle between each stack

    std::vector<Point3> points;

    // for each stack
    for (int i = 0; i <= stacks; i++) {
        double beta = i * sliceStep - M_PI_2f; // angle of current stack
        // for each slice
        for (int j = 0; j <= slices; j++) {
            double alpha = j * stackStep; // angle of current slice
            int heightMapIndex = (int) round((stacks - i) * ratioH) * tw + (int) round(j * ratioW);
            double heightRadius = radius * (1 + heightScale * imageData[heightMapIndex] / 255.0);
            points.push_back(Point3::polar(heightRadius, alpha, beta));
        }
    }

    std::vector<Vertex> grid;

    for (int i = 0; i <= slices; i++) {
        Point3 p = points[i];
        grid.emplace_back(p, Vector3(p).normalize(), Vector2((double) i / slices, 0));
    }

    // for each stack
    for (int i = 1; i < stacks; i++) {
        double texY = (double) i / stacks;
        // for each slice
        grid.emplace_back(points[i * (slices + 1)], Vector3(points[i * (slices + 1)]).normalize(), Vector2(0, texY));
        for (int j = 1; j < slices; j++) {
            double texX = (double) j / slices;

            Point3 p = points[i * (slices + 1) + j];
            Point3 pOver = points[(i + 1) * (slices + 1) + j];
            Point3 pUnder = points[(i - 1) * (slices + 1) + j];
            Point3 pLeft = points[i * (slices + 1) + j - 1];
            Point3 pRight = points[i * (slices + 1) + j + 1];
            Vector3 h(pOver, pUnder);
            Vector3 v(pLeft, pRight);
            Vector3 n = h.cross(v).normalize();

            grid.emplace_back(p, n, Vector2(texX, texY));
        }
        grid.emplace_back(points[i * (slices + 1) + slices], Vector3(points[i * (slices + 1) + slices]).normalize(), Vector2(1, texY));
    }

    for (int i = 0; i <= slices; i++) {
        Point3 p = points[stacks * (slices + 1) + i];
        grid.emplace_back(p, Vector3(p).normalize(), Vector2((double) i / slices, 1));
    }

    buildSphere(slices, stacks, grid);
}

void Sphere::buildSphere(int slices, int stacks, const std::vector<Vertex> &grid)
{
    // bottom and top cone, one triangle per slice
    int top = (slices + 1) * (stacks - 1);
    for (int i = 0; i < slices; i++) {
        vertices.push_back(grid[i + 1]);
        vertices.push_back(grid[i + slices + 2]);
        vertices.push_back(grid[i + slices + 1]);

        vertices.push_back(grid[top + i]);
        vertices.push_back(grid[top + i + 1]);
        vertices.push_back(grid[top + i + slices + 2]);
    }

    // middle part, two triangles per slice
    for (int i = 1; i < stacks - 1; i++) {
        for (int j = 0; j < slices; j++) {
            int bottomLeft = i * (slices + 1) + j;
            int bottomRight = i * (slices + 1) + j + 1;
            int topLeft = (i + 1) * (slices + 1) + j;
            int topRight = (i + 1) * (slices + 1) + j + 1;

            vertices.push_back(grid[bottomLeft]);
            vertices.push_back(grid[bottomRight]);
            vertices.push_back(grid[topLeft]);

            vertices.push_back(grid[topLeft]);
            vertices.push_back(grid[bottomRight]);
            vertices.push_back(grid[topRight]);
        }
    }
}