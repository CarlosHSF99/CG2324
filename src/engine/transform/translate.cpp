#include <GL/glut.h>
#include "deps/tinyxml2.h"
#include "engine/transform.h"

using namespace tinyxml2;

namespace transform
{
    Translate::Translate(XMLElement *transformElement)
    {
        vector = Vector3(transformElement);
    }

    void Translate::apply(float) noexcept
    {
        glTranslatef(this->vector.x, this->vector.y, this->vector.z);
    }
}
