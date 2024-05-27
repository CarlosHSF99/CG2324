#include <GL/glew.h>
#include "deps/tinyxml2.h"
#include "engine/scene/light.h"

using namespace tinyxml2;

PointLight::PointLight(XMLElement *lightElement)
{
    lightElement->QueryFloatAttribute("posx", &pos.x);
    lightElement->QueryFloatAttribute("posy", &pos.y);
    lightElement->QueryFloatAttribute("posz", &pos.z);
}

void PointLight::place() const noexcept
{
    float posv[4] = {pos.x, pos.y, pos.z, 1.0f};
    glLightfv(id, GL_POSITION, posv);
}
