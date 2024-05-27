#include <GL/glew.h>
#include "engine/scene/light.h"

Light::Light()
{
    static GLenum nextLightID = GL_LIGHT0;

    id = nextLightID++;

    static GLfloat dark[4] = {0.0f, 0.0f, 0.0f, 1.0f};
    static GLfloat white[4] = {1.0f, 1.0f, 1.0f, 1.0f};

    glEnable(id);
    glLightfv(id, GL_AMBIENT, dark);
    glLightfv(id, GL_DIFFUSE, white);
    glLightfv(id, GL_SPECULAR, white);
}
