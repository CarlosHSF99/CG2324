#include <GL/glut.h>
#include "deps/tinyxml2.h"
#include "engine/scene/transform.h"

using namespace tinyxml2;

Translate::Translate(XMLElement *transformElement)
{
    vector = Vector3(transformElement);
}

void Translate::apply(float) noexcept
{
    glTranslatef(this->vector.x, this->vector.y, this->vector.z);
}
