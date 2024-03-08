#include <cmath>
#include "generator/sphere.h"

Sphere::Sphere(double radius, int slices, int stacks)
{
    double stackStep = 2 * M_PI / slices; // angle between each slice
    double sliceStep = M_PI / stacks; // angle between each stack

    // bottom and top caps
    double betaBot = M_PI_2 + sliceStep; // angle of bottom cap
    double betaTop = M_PI_2 - sliceStep; // angle of top cap
    double yCap = radius * sin(M_PI_2 - sliceStep); // modulus of height of the caps

    for (int i = 0; i < slices; i++) {
        double alpha1 = i * stackStep; // angle of current slice
        double alpha2 = (i + 1) * stackStep; // angle of next slice

        // bottom cap, top right vertex
        double xBot1 = radius * cos(betaBot) * sin(alpha2);
        double zBot1 = radius * cos(betaBot) * cos(alpha2);

        // bottom cap, top left vertex
        double xBot2 = radius * cos(betaBot) * sin(alpha1);
        double zBot2 = radius * cos(betaBot) * cos(alpha1);

        // bottom cap triangle
        vertices.emplace_back(0, -radius, 0);
        vertices.emplace_back(xBot1, -yCap, zBot1);
        vertices.emplace_back(xBot2, -yCap, zBot2);

        // top cap bottom right vertex
        double xTop1 = radius * cos(betaTop) * sin(alpha1);
        double zTop1 = radius * cos(betaTop) * cos(alpha1);

        // top cap, bottom left vertex
        double xTop2 = radius * cos(betaTop) * sin(alpha2);
        double zTop2 = radius * cos(betaTop) * cos(alpha2);

        // top cap triangle
        vertices.emplace_back(0, radius, 0);
        vertices.emplace_back(xTop1, yCap, zTop1);
        vertices.emplace_back(xTop2, yCap, zTop2);
    }


    // curved surface
    // for each stack
    for (int i = 1; i < stacks - 1; i++) {
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
            double x4 = radius * cos(beta2) * sin(alpha2);
            double z4 = radius * cos(beta2) * cos(alpha2);

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
