#include "deps/tinyxml2.h"
#include "engine/scene/window.h"

using namespace tinyxml2;

Window::Window(XMLElement *windowElement)
{
    windowElement->QueryIntAttribute("x", &x);
    windowElement->QueryIntAttribute("y", &y);
    windowElement->QueryIntAttribute("width", &width);
    windowElement->QueryIntAttribute("height", &height);
}
