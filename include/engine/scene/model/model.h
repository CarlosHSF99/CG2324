#ifndef CG2324_ENGINE_MODEL_H
#define CG2324_ENGINE_MODEL_H


#include "deps/tinyxml2.h"
#include "vertex_buffers.h"
#include "texture.h"
#include "engine/scene/model/color/color.h"
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
