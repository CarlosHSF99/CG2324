#include <cmath>
#include "utils/cone.h"

Cone::Cone(float radius, float height, int slices, int stacks)
{
    double stackStep = 2 * M_PI / slices; // angle between each slice
    double sliceStep = height / (float) stacks; // height between each stack

    // circular base
    for (int i = 0; i < slices; i++) {
        double alpha1 = i * stackStep; // current angle
        double alpha2 = (i + 1) * stackStep; // next angle

        // bottom left vertex
        double x1 = radius * sin(alpha2);
        double z1 = radius * cos(alpha2);

        // bottom right vertex
        double x2 = radius * sin(alpha1);
        double z2 = radius * cos(alpha1);

        // triangle
        vertices.emplace_back(0, 0, 0);
        vertices.emplace_back(x1, 0, z1);
        vertices.emplace_back(x2, 0, z2);
    }

    // curved surface
    // for each stack
    for (int i = 0; i < stacks; i++) {
        double y1 = i * sliceStep; // current height
        double y2 = (i + 1) * sliceStep; // next height

        double radius1 = (float) (stacks - i) * radius / (float) stacks; // current radius
        double radius2 = (float) (stacks - i - 1) * radius / (float) stacks; // next radius

        // for each slice
        for (int j = 0; j < slices; j++) {
            double alpha1 = j * stackStep;
            double alpha2 = (j + 1) * stackStep;

            // bottom left
            double x1 = radius1 * sin(alpha1);
            double z1 = radius1 * cos(alpha1);

            // bottom right
            double x2 = radius1 * sin(alpha2);
            double z2 = radius1 * cos(alpha2);

            // top left
            double x3 = radius2 * sin(alpha1);
            double z3 = radius2 * cos(alpha1);

            // top right
            double x4 = radius2 * sin(alpha2);
            double z4 = radius2 * cos(alpha2);

            // first triangle
            vertices.emplace_back(x1, y1, z1);
            vertices.emplace_back(x2, y1, z2);
            vertices.emplace_back(x3, y2, z3);

            // second triangle
            vertices.emplace_back(x3, y2, z3);
            vertices.emplace_back(x2, y1, z2);
            vertices.emplace_back(x4, y2, z4);
        }
    }
}
