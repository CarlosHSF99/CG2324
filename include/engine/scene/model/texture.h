#ifndef CG2324_TEXTURE_H
#define CG2324_TEXTURE_H


#include <GL/glew.h>
#include "deps/tinyxml2.h"

struct Texture
{
    GLuint id{};

    Texture() = default;

    explicit Texture(GLuint id) : id(id) {}

    explicit Texture(tinyxml2::XMLElement *textureElement);

    void bind() const;
};


#endif //CG2324_TEXTURE_H
