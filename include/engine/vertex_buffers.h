#ifndef CG2324_VERTEX_BUFFERS_H
#define CG2324_VERTEX_BUFFERS_H

#include <GL/glew.h>
#include <vector>

struct Point3;
struct Vector2;
struct Vector3;

class VertexBuffers
{
public:
    GLuint positionsBuffer{};
    GLuint normalsBuffer{};
    GLuint texCoordsBuffer{};
    GLsizei size{};

public:
    VertexBuffers() = default;

    VertexBuffers(const std::vector<Point3> &positions, const std::vector<Vector3> &normals, const std::vector<Vector2> &texCoords);

    void draw() const;
};


#endif //CG2324_VERTEX_BUFFERS_H
