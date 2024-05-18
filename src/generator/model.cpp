#include <fstream>
#include <iostream>
#include "utils/vertex.h"
#include "generator/model.h"

using std::cerr, std::endl, std::ios, std::ofstream, std::string;

void Model::writeToFile(const string &filename) const
{
    ofstream file(filename, ios::binary);

    if (!file.is_open()) {
        cerr << "Error opening file " << filename << endl;
        return;
    }

    file.write(reinterpret_cast<const char *>(vertices.data()),
               static_cast<std::streamsize>(vertices.size() * sizeof(Vertex)));
}
