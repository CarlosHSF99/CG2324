#ifndef CG2324_ENGINE_MODEL_H
#define CG2324_ENGINE_MODEL_H


#include "deps/tinyxml2.h"
#include "engine/vertex_buffers.h"
#include "engine/texture.h"
#include "engine/color.h"
#include <GL/glew.h>
#include <GL/glut.h>
#include <vector>

class Model
{
public:
    VertexBuffers vbos;
    Texture texture;
    Color color;

public:
    Model() = default;

    explicit Model(tinyxml2::XMLElement *modelElement);

    void draw() const;
};


#endif //CG2324_ENGINE_MODEL_H
