#ifndef CG2324_ENGINE_MODEL_H
#define CG2324_ENGINE_MODEL_H


#include "deps/tinyxml2.h"
#include "utils/point3.h"
#include "engine/color.h"
#include "engine/vertex_buffers.h"

#include <GL/glew.h>
#include <GL/glut.h>
#include <vector>

class Model
{
public:
    VertexBuffers vbos;
    Color color;

public:
    Model() = default;

    explicit Model(tinyxml2::XMLElement *modelElement);

    explicit Model(VertexBuffers vbos) : vbos(vbos) {}

    void draw() const;
};


#endif //CG2324_ENGINE_MODEL_H
