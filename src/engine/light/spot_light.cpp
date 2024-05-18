#include <GL/glew.h>
#include "deps/tinyxml2.h"
#include "engine/light.h"

using namespace tinyxml2;

SpotLight::SpotLight(XMLElement *lightElement)
{
    lightElement->QueryFloatAttribute("posX", &pos.x);
    lightElement->QueryFloatAttribute("posY", &pos.y);
    lightElement->QueryFloatAttribute("posZ", &pos.z);

    lightElement->QueryFloatAttribute("dirX", &dir.x);
    lightElement->QueryFloatAttribute("dirY", &dir.y);
    lightElement->QueryFloatAttribute("dirZ", &dir.z);

    lightElement->QueryFloatAttribute("cutoff", &cutoff);
}

auto SpotLight::place() const noexcept -> void
{
    float posv[4] = {pos.x, pos.y, pos.z, 1.0f};
    float dirv[4] = {dir.x, dir.y, dir.z, 0.0f};
    glLightfv(id, GL_POSITION, posv);
    glLightfv(id, GL_SPOT_DIRECTION, dirv);
    glLightf(id, GL_SPOT_CUTOFF, cutoff);
}

