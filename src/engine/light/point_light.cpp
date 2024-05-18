#include <GL/glew.h>
#include "deps/tinyxml2.h"
#include "engine/light.h"

using namespace tinyxml2;

PointLight::PointLight(XMLElement *lightElement)
{
    lightElement->QueryFloatAttribute("posX", &pos.x);
    lightElement->QueryFloatAttribute("posY", &pos.y);
    lightElement->QueryFloatAttribute("posZ", &pos.z);
}

void PointLight::place() const noexcept
{
    float posv[4] = {pos.x, pos.y, pos.z, 1.0f};
    glLightfv(id, GL_POSITION, posv);
}
