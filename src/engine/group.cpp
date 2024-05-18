#include <map>
#include "deps/tinyxml2.h"
#include "engine/transform.h"
#include "engine/group.h"

using namespace tinyxml2;
using namespace transform;

Group::Group(XMLElement *groupElement)
{
    XMLElement *transformsElement = groupElement->FirstChildElement("transform");
    if (transformsElement) {
        XMLElement *transformElement = transformsElement->FirstChildElement();
        while (transformElement) {
            if (transformElement->Name() == std::string("translate")) {
                if (transformElement->Attribute("time")) {
                    transforms.push_back(std::make_unique<TimedTranslate>(transformElement));
                } else {
                    transforms.push_back(std::make_unique<Translate>(transformElement));
                }
            } else if (transformElement->Name() == std::string("rotate")) {
                if (transformElement->Attribute("time")) {
                    transforms.push_back(std::make_unique<TimedRotate>(transformElement));
                } else {
                    transforms.push_back(std::make_unique<Rotate>(transformElement));
                }
            } else if (transformElement->Name() == std::string("scale")) {
                transforms.push_back(std::make_unique<Scale>(transformElement));
            }
            transformElement = transformElement->NextSiblingElement();
        }
    }

    XMLElement *modelsElement = groupElement->FirstChildElement("models");
    if (modelsElement) {
        XMLElement *modelElement = modelsElement->FirstChildElement("model");
        while (modelElement) {
            models.emplace_back(modelElement);
            modelElement = modelElement->NextSiblingElement("model");
        }
    }

    XMLElement *subgroupElement = groupElement->FirstChildElement("group");
    while (subgroupElement) {
        subgroups.emplace_back(subgroupElement);
        subgroupElement = subgroupElement->NextSiblingElement("group");
    }
}

void Group::draw(float time) const
{
    glPushMatrix();

    for (const auto &transform: this->transforms) {
        transform->apply(time);
    }

    for (const auto &model: this->models) {
        model.draw();
    }

    for (const auto &group: this->subgroups) {
        group.draw(time);
    }

    glPopMatrix();
}
