#include <GL/glew.h>
#include "deps/tinyxml2.h"
#include "engine/color.h"

using namespace tinyxml2;

Color::Color(XMLElement *colorElement)
{
    XMLElement *diffuseElement = colorElement->FirstChildElement("diffuse");
    if (diffuseElement) {
        diffuse = ColorRGB(diffuseElement);
    }
    XMLElement *ambientElement = colorElement->FirstChildElement("ambient");
    if (ambientElement) {
        ambient = ColorRGB(ambientElement);
    }
    XMLElement *specularElement = colorElement->FirstChildElement("specular");
    if (specularElement) {
        specular = ColorRGB(specularElement);
    }
    XMLElement *emissiveElement = colorElement->FirstChildElement("emissive");
    if (emissiveElement) {
        emissive = ColorRGB(emissiveElement);
    }
    XMLElement *shininessElement = colorElement->FirstChildElement("shininess");
    if (shininessElement) {
        shininessElement->QueryFloatAttribute("value", &shininess);
    }
}

void Color::set() const {
    float d[] = {diffuse.r, diffuse.g, diffuse.b, 1.0f};
    float a[] = {ambient.r, ambient.g, ambient.b, 1.0f};
    float s[] = {specular.r, specular.g, specular.b, 1.0f};
    float e[] = {emissive.r, emissive.g, emissive.b, 1.0f};
    glMaterialfv(GL_FRONT, GL_DIFFUSE, d);
    glMaterialfv(GL_FRONT, GL_AMBIENT, a);
    glMaterialfv(GL_FRONT, GL_SPECULAR, s);
    glMaterialfv(GL_FRONT, GL_EMISSION, e);
    glMaterialf(GL_FRONT, GL_SHININESS, shininess);
}
