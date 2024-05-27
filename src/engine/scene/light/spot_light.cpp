#include <GL/glew.h>
#include "deps/tinyxml2.h"
#include "engine/scene/light.h"

using namespace tinyxml2;

SpotLight::SpotLight(XMLElement *lightElement)
{
    lightElement->QueryFloatAttribute("posx", &pos.x);
    lightElement->QueryFloatAttribute("posy", &pos.y);
    lightElement->QueryFloatAttribute("posz", &pos.z);

    lightElement->QueryFloatAttribute("dirx", &dir.x);
    lightElement->QueryFloatAttribute("diry", &dir.y);
    lightElement->QueryFloatAttribute("dirz", &dir.z);

    lightElement->QueryFloatAttribute("cutoff", &cutoff);
}

void SpotLight::place() const noexcept
{
    float posv[4] = {pos.x, pos.y, pos.z, 1.0f};
    float dirv[4] = {dir.x, dir.y, dir.z, 0.0f};
    glLightfv(id, GL_POSITION, posv);
    glLightfv(id, GL_SPOT_DIRECTION, dirv);
    glLightf(id, GL_SPOT_CUTOFF, cutoff);
}

