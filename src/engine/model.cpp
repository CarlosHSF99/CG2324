#include <ostream>
#include <fstream>
#include <iostream>
#include "engine/model.h"

using std::cerr, std::endl, std::ifstream, std::ios, std::string, std::vector;

Model::Model(const string &filename)
{
    ifstream file(filename, ios::binary);

    if (!file.is_open()) {
        cerr << "Error opening file " << filename << endl;
        return;
    }

    vector<Point3> vertices;

    float coords[3];
    while (file.read(reinterpret_cast<char *>(coords), sizeof(coords))) {
        vertices.emplace_back(coords[0], coords[1], coords[2]);
    }

    size = (GLsizei) vertices.size();

    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, (GLsizeiptr) (3 * size * sizeof(float)), vertices.data(), GL_STATIC_DRAW);
}

void Model::draw() const
{
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glVertexPointer(3, GL_FLOAT, 0, nullptr);
    glDrawArrays(GL_TRIANGLES, 0, size);
}
