#include <GL/glew.h>
#include "engine/vertex_buffers.h"

VertexBuffers::VertexBuffers(const std::vector<Point3> &coords, const std::vector<Vector3> &normals)
{
    size = (GLsizei) coords.size();

    glGenBuffers(1, &coordsBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, coordsBuffer);
    glBufferData(GL_ARRAY_BUFFER, (GLsizeiptr) (3 * size * sizeof(float)), coords.data(), GL_STATIC_DRAW);

    glGenBuffers(1, &normalsBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, normalsBuffer);
    glBufferData(GL_ARRAY_BUFFER, (GLsizeiptr) (3 * size * sizeof(float)), normals.data(), GL_STATIC_DRAW);
}

void VertexBuffers::draw() const
{
    glBindBuffer(GL_ARRAY_BUFFER, coordsBuffer);
    glVertexPointer(3, GL_FLOAT, 0, nullptr);

    glBindBuffer(GL_ARRAY_BUFFER, normalsBuffer);
    glNormalPointer(GL_FLOAT, 0, nullptr);

    glDrawArrays(GL_TRIANGLES, 0, size);
}
