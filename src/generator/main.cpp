#include <iostream>
#include <fstream>
#include "utils/plane.h"
#include "utils/box.h"

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
        cout << "implement sphere" << endl;
    } else if (type == "cone") {
        cout << "implement cone" << endl;
    } else {
        cout << "Invalid type" << endl;
    }

    return 0;
}
