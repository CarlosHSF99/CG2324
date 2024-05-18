#ifndef CG2324_VERTEX_BUFFERS_H
#define CG2324_VERTEX_BUFFERS_H

#include <GL/glew.h>
#include <vector>
#include "utils/point3.h"
#include "utils/vector3.h"

class VertexBuffers
{
public:
    GLuint coordsBuffer{};
    GLuint normalsBuffer{};
    GLsizei size{};

public:
    VertexBuffers() = default;

    VertexBuffers(const std::vector<Point3> &coords, const std::vector<Vector3> &normals);

    void draw() const;
};


#endif //CG2324_VERTEX_BUFFERS_H
