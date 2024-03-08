#include <iostream>
#include <fstream>
#include "generator/plane.h"
#include "generator/box.h"
#include "generator/sphere.h"
#include "generator/cone.h"

using std::cout, std::endl, std::string, std::ofstream, std::ifstream, std::tuple;

int main(int argc, char **argv)
{
    auto type = std::string_view(argv[1]);

    if (type == "plane") {
        auto size = std::stof(argv[2]);
        auto divisions = std::stoi(argv[3]);
        Plane plane(size, divisions);
        plane.writeToFile(argv[4]);
    } else if (type == "box") {
        auto size = std::stof(argv[2]);
        auto divisions = std::stoi(argv[3]);
        Box box(size, divisions);
        box.writeToFile(argv[4]);
    } else if (type == "sphere") {
        auto radius = std::stof(argv[2]);
        auto slices = std::stoi(argv[3]);
        auto stacks = std::stoi(argv[4]);
        Sphere sphere(radius, slices, stacks);
        sphere.writeToFile(argv[5]);
    } else if (type == "cone") {
        auto radius = std::stof(argv[2]);
        auto height = std::stof(argv[3]);
        auto slices = std::stoi(argv[4]);
        auto stacks = std::stoi(argv[5]);
        Cone cone(radius, height, slices, stacks);
        cone.writeToFile(argv[6]);
    } else {
        cout << "Invalid type" << endl;
    }

    return 0;
}
