#ifndef CG2324_COLOR_H
#define CG2324_COLOR_H


#include "color_rgb.h"
#include "deps/tinyxml2.h"

class Color
{
public:
    ColorRGB diffuse{200, 200, 200};
    ColorRGB ambient{50, 50, 50};
    ColorRGB specular{0, 0, 0};
    ColorRGB emissive{0, 0, 0};
    float shininess{0};

public:
    Color() = default;

    Color(const ColorRGB &diffuse, const ColorRGB &ambient, const ColorRGB &specular, const ColorRGB &emission,
          float shininess) :
            diffuse(diffuse), ambient(ambient), specular(specular), emissive(emission), shininess(shininess) {}

    explicit Color(tinyxml2::XMLElement *colorElement);

    void set() const;
};


#endif //CG2324_COLOR_H
