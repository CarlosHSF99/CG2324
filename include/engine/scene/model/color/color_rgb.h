#ifndef CG2324_COLOR_RGB_H
#define CG2324_COLOR_RGB_H

#include "deps/tinyxml2.h"

struct ColorRGB
{
public:
    float r{};
    float g{};
    float b{};

public:
    ColorRGB() : r(0), g(0), b(0) {}

    ColorRGB(float r, float g, float b);

    explicit ColorRGB(tinyxml2::XMLElement *colorElement);
};


#endif //CG2324_COLOR_RGB_H
