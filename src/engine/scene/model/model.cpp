#include <map>
#include <ostream>
#include <fstream>
#include <iostream>
#include "deps/tinyxml2.h"
#include "utils/point3.h"
#include "utils/vector2.h"
#include "utils/vector3.h"
#include "engine/scene/model/vertex_buffers.h"
#include "engine/scene/model/model.h"

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

        vector<Point3> positions;
        vector<Vector3> normals;
        vector<Vector2> texCoords;

        float vertex[8];
        while (file.read(reinterpret_cast<char *>(vertex), sizeof(vertex))) {
            positions.emplace_back(vertex[0], vertex[1], vertex[2]);
            normals.emplace_back(vertex[3], vertex[4], vertex[5]);
            texCoords.emplace_back(vertex[6], vertex[7]);
        }

        vbos = VertexBuffers(positions, normals, texCoords);
        vertexBuffers[filename] = vbos;
    }

    XMLElement *textureElement = modelElement->FirstChildElement("texture");
    if (textureElement) {
        texture = Texture(textureElement);
    }

    XMLElement *colorElement = modelElement->FirstChildElement("color");
    if (colorElement) {
        color = Color(colorElement);
    }
}

void Model::draw() const
{
    color.set();
    texture.bind();
    vbos.draw();
}
