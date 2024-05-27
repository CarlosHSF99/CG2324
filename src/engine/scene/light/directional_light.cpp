#include <GL/glew.h>
#include "deps/tinyxml2.h"
#include "engine/scene/light.h"

using namespace tinyxml2;

DirectionalLight::DirectionalLight(XMLElement *lightElement)
{
    lightElement->QueryFloatAttribute("dirx", &dir.x);
    lightElement->QueryFloatAttribute("diry", &dir.y);
    lightElement->QueryFloatAttribute("dirz", &dir.z);
}

void DirectionalLight::place() const noexcept
{
    float dirv[4] = {dir.x, dir.y, dir.z, 0.0f};
    glLightfv(id, GL_POSITION, dirv);
}

