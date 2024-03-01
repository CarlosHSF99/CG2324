#include <cmath>
#include "utils/sphere.h"

Sphere::Sphere(double radius, int slices, int stacks)
{
    double stackStep = 2 * M_PI / slices; // angle between each slice
    double sliceStep = M_PI / stacks; // angle between each stack

    // for each stack
    for (int i = 0; i < stacks; i++) {
        double beta1 = i * sliceStep - M_PI_2; // angle of current stack
        double beta2 = (i + 1) * sliceStep - M_PI_2; // angle of next stack

        double y1 = radius * sin(beta1); // height of current stack
        double y2 = radius * sin(beta2); // height of next stack

        // for each slice
        for (int j = 0; j < slices; j++) {
            double alpha1 = j * stackStep; // angle of current slice
            double alpha2 = (j + 1) * stackStep; // angle of next slice

            // bottom left vertex
            double x1 = radius * cos(beta1) * sin(alpha1);
            double z1 = radius * cos(beta1) * cos(alpha1);

            // bottom right vertex
            double x2 = radius * cos(beta1) * sin(alpha2);
            double z2 = radius * cos(beta1) * cos(alpha2);

            // top left vertex
            double x3 = radius * cos(beta2) * sin(alpha1);
            double z3 = radius * cos(beta2) * cos(alpha1);

            // top right vertex
            double z4 = radius * cos(beta2) * cos(alpha2);
            double x4 = radius * cos(beta2) * sin(alpha2);

            // first (bottom left) triangle
            vertices.emplace_back(x1, y1, z1);
            vertices.emplace_back(x2, y1, z2);
            vertices.emplace_back(x3, y2, z3);

            // second (bottom right) triangle
            vertices.emplace_back(x3, y2, z3);
            vertices.emplace_back(x2, y1, z2);
            vertices.emplace_back(x4, y2, z4);
        }
    }
}
