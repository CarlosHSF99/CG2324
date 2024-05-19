#include <map>
#include <ostream>
#include <fstream>
#include <iostream>
#include "deps/tinyxml2.h"
#include "engine/vertex_buffers.h"
#include "engine/model.h"

using std::cerr, std::endl, std::ifstream, std::ios, std::map, std::string, std::vector;
using namespace tinyxml2;

Model::Model(XMLElement *modelElement)
{
    static map<string, VertexBuffers> vertexBuffers;

    const char *filename = modelElement->Attribute("file");

    if (vertexBuffers.find(filename) != vertexBuffers.end()) {
        vbos = vertexBuffers[filename];
    } else {
        ifstream file(filename, ios::binary);

        if (!file.is_open()) {
            cerr << "Error opening file " << filename << endl;
            return;
        }

        vector<Point3> coords;
        vector<Vector3> normals;

        float vertex[6];
        while (file.read(reinterpret_cast<char *>(vertex), sizeof(vertex))) {
            coords.emplace_back(vertex[0], vertex[1], vertex[2]);
            normals.emplace_back(vertex[3], vertex[4], vertex[5]);
        }

        vbos = VertexBuffers(coords, normals);
        vertexBuffers[filename] = vbos;
    }

    XMLElement *colorElement = modelElement->FirstChildElement("color");
    if (colorElement) {
        color = Color(colorElement);
    }
}

void Model::draw() const
{
    color.set();
    vbos.draw();
}
