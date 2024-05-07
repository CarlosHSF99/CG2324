#ifndef CG2324_ENGINE_MODEL_H
#define CG2324_ENGINE_MODEL_H


#include "utils/point3.h"

#include <GL/glew.h>
#include <GL/glut.h>
#include <vector>

class Model
{
private:
    GLuint buffer{};
    GLsizei size{};

public:
    Model() = default;

    explicit Model(const std::string &filename);

    void draw() const;
};


#endif //CG2324_ENGINE_MODEL_H
