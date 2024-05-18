#include <GL/glew.h>
#include "deps/tinyxml2.h"
#include "engine/light.h"

using namespace tinyxml2;

DirectionalLight::DirectionalLight(XMLElement *lightElement)
{
    lightElement->QueryFloatAttribute("dirX", &dir.x);
    lightElement->QueryFloatAttribute("dirY", &dir.y);
    lightElement->QueryFloatAttribute("dirZ", &dir.z);
}

auto DirectionalLight::place() const noexcept -> void
{
    float dirv[4] = {dir.x, dir.y, dir.z, 0.0f};
    glLightfv(id, GL_POSITION, dirv);
}

