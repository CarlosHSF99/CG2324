#include <GL/glut.h>
#include "deps/tinyxml2.h"
#include "engine/transform.h"

using namespace tinyxml2;

namespace transform
{
    Rotate::Rotate(XMLElement *transformElement)
    {
        transformElement->QueryFloatAttribute("angle", &angle);
        vector = Vector3(transformElement);
    }

    void Rotate::apply(float) noexcept
    {
        glRotatef(this->angle, this->vector.x, this->vector.y, this->vector.z);
    }
}
