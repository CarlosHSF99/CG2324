#include <GL/glew.h>
#include "utils/point3.h"
#include "utils/vector2.h"
#include "utils/vector3.h"
#include "engine/vertex_buffers.h"

using std::vector;

VertexBuffers::VertexBuffers(const vector<Point3> &positions, const vector<Vector3> &normals, const vector<Vector2> &texCoords)
{
    size = (GLsizei) positions.size();

    glGenBuffers(1, &positionsBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, positionsBuffer);
    glBufferData(GL_ARRAY_BUFFER, (GLsizeiptr) (3 * size * sizeof(float)), positions.data(), GL_STATIC_DRAW);

    glGenBuffers(1, &normalsBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, normalsBuffer);
    glBufferData(GL_ARRAY_BUFFER, (GLsizeiptr) (3 * size * sizeof(float)), normals.data(), GL_STATIC_DRAW);

    glGenBuffers(1, &texCoordsBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, texCoordsBuffer);
    glBufferData(GL_ARRAY_BUFFER, (GLsizeiptr) (2 * size * sizeof(float)), texCoords.data(), GL_STATIC_DRAW);
}

void VertexBuffers::draw() const
{
    glBindBuffer(GL_ARRAY_BUFFER, positionsBuffer);
    glVertexPointer(3, GL_FLOAT, 0, nullptr);

    glBindBuffer(GL_ARRAY_BUFFER, normalsBuffer);
    glNormalPointer(GL_FLOAT, 0, nullptr);

    glBindBuffer(GL_ARRAY_BUFFER, texCoordsBuffer);
    glTexCoordPointer(2, GL_FLOAT, 0, nullptr);

    glDrawArrays(GL_TRIANGLES, 0, size);

    glBindTexture(GL_TEXTURE_2D, 0);
}
