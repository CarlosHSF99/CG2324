#include <GL/glut.h>
#include "deps/tinyxml2.h"
#include "engine/transform.h"

using namespace tinyxml2;

namespace transform
{
    Scale::Scale(XMLElement *transformElement)
    {
        transformElement->QueryFloatAttribute("x", &factorX);
        transformElement->QueryFloatAttribute("y", &factorY);
        transformElement->QueryFloatAttribute("z", &factorZ);
    }

    void Scale::apply(float) noexcept
    {
        glScalef(this->factorX, this->factorY, this->factorZ);
    }
}
