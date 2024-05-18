#include "deps/tinyxml2.h"
#include "engine/color_rgb.h"

using namespace tinyxml2;

ColorRGB::ColorRGB(float r, float g, float b)
        : r(r / 255.0f), g(g / 255.0f), b(b / 255.0f) {}

ColorRGB::ColorRGB(tinyxml2::XMLElement *colorElement)
{
    colorElement->QueryFloatAttribute("R", &r);
    colorElement->QueryFloatAttribute("G", &g);
    colorElement->QueryFloatAttribute("B", &b);
    r /= 255.0f;
    g /= 255.0f;
    b /= 255.0f;
}