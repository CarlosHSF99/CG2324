#include <string>
#include <iostream>
#include <map>
#include "deps/tinyxml2.h"
#include "engine/world.h"
#include "engine/model.h"
#include "engine/xml_world_loader.h"

using namespace tinyxml2;

Group parseGroup(XMLElement *groupElement);

namespace XMLWorldLoader
{
    Window loadWindow(char *filename)
    {
        int x{}, y{}, width{}, height{};

        XMLDocument doc;
        if (doc.LoadFile(filename) == XML_SUCCESS) {
            XMLElement *worldElement = doc.FirstChildElement("world");
            if (worldElement) {
                XMLElement *windowElement = worldElement->FirstChildElement("window");
                if (windowElement) {
                    windowElement->QueryIntAttribute("x", &x);
                    windowElement->QueryIntAttribute("y", &y);
                    windowElement->QueryIntAttribute("width", &width);
                    windowElement->QueryIntAttribute("height", &height);
                }
            }
        } else {
            std::cerr << "Failed to loadWorld file." << std::endl;
        }

        return {x, y, width, height, filename};
    }

    World loadWorld(char *filename)
    {
        float positionX{}, positionY{}, positionZ{};
        float lookAtX{}, lookAtY{}, lookAtZ{};
        float upX{}, upY{}, upZ{};
        float fov{}, near{}, far{};
        Group topGroup;

        XMLDocument doc;
        if (doc.LoadFile(filename) == XML_SUCCESS) {
            XMLElement *worldElement = doc.FirstChildElement("world");
            if (worldElement) {
                XMLElement *cameraElement = worldElement->FirstChildElement("camera");
                if (cameraElement) {
                    XMLElement *positionElement = cameraElement->FirstChildElement("position");
                    if (positionElement) {
                        positionElement->QueryFloatAttribute("x", &positionX);
                        positionElement->QueryFloatAttribute("y", &positionY);
                        positionElement->QueryFloatAttribute("z", &positionZ);
                    }
                    XMLElement *lookAtElement = cameraElement->FirstChildElement("lookAt");
                    if (lookAtElement) {
                        lookAtElement->QueryFloatAttribute("x", &lookAtX);
                        lookAtElement->QueryFloatAttribute("y", &lookAtY);
                        lookAtElement->QueryFloatAttribute("z", &lookAtZ);
                    }
                    XMLElement *upElement = cameraElement->FirstChildElement("up");
                    if (upElement) {
                        upElement->QueryFloatAttribute("x", &upX);
                        upElement->QueryFloatAttribute("y", &upY);
                        upElement->QueryFloatAttribute("z", &upZ);
                    }
                    XMLElement *projectionElement = cameraElement->FirstChildElement("projection");
                    if (projectionElement) {
                        projectionElement->QueryFloatAttribute("fov", &fov);
                        projectionElement->QueryFloatAttribute("near", &near);
                        projectionElement->QueryFloatAttribute("far", &far);
                    }
                }

                XMLElement *groupElement = worldElement->FirstChildElement("group");
                if (groupElement) {
                    topGroup = parseGroup(groupElement);
                }
            }
        } else {
            std::cerr << "Failed to load file." << std::endl;
        }

        Camera camera({positionX, positionY, positionZ}, {lookAtX, lookAtY, lookAtZ}, {upX, upY, upZ}, fov, near, far);

        return {camera, std::move(topGroup)};
    }
}

Group parseGroup(XMLElement *groupElement)
{
    static std::map<std::string, Model> modelBuffers;

    std::vector<std::unique_ptr<Transform>> transforms;
    std::vector<Model> models;
    std::vector<Group> subgroups;

    XMLElement *transformsElement = groupElement->FirstChildElement("transform");
    if (transformsElement) {
        XMLElement *transformElement = transformsElement->FirstChildElement();
        while (transformElement) {
            if (transformElement->Name() == std::string("translate")) {
                if (transformElement->Attribute("time")) {
                    float time;
                    bool align, draw;
                    std::vector<Point3> points;
                    transformElement->QueryFloatAttribute("time", &time);
                    transformElement->QueryBoolAttribute("align", &align);
                    transformElement->QueryBoolAttribute("draw", &draw);
                    XMLElement *pointElement = transformElement->FirstChildElement("point");
                    while (pointElement) {
                        float x, y, z;
                        pointElement->QueryFloatAttribute("x", &x);
                        pointElement->QueryFloatAttribute("y", &y);
                        pointElement->QueryFloatAttribute("z", &z);
                        points.emplace_back(x, y, z);
                        pointElement = pointElement->NextSiblingElement("point");
                    }
                    transforms.push_back(std::make_unique<TimedTranslate>(time, align, draw, std::move(points)));
                } else {
                    float x, y, z;
                    transformElement->QueryFloatAttribute("x", &x);
                    transformElement->QueryFloatAttribute("y", &y);
                    transformElement->QueryFloatAttribute("z", &z);
                    transforms.push_back(std::make_unique<Translate>(x, y, z));
                }
            } else if (transformElement->Name() == std::string("rotate")) {
                float x, y, z;
                transformElement->QueryFloatAttribute("x", &x);
                transformElement->QueryFloatAttribute("y", &y);
                transformElement->QueryFloatAttribute("z", &z);
                if (transformElement->Attribute("time")) {
                    float time;
                    transformElement->QueryFloatAttribute("time", &time);
                    transforms.push_back(std::make_unique<TimedRotate>(time, x, y, z));
                } else {
                    float angle;
                    transformElement->QueryFloatAttribute("angle", &angle);
                    transforms.push_back(std::make_unique<Rotate>(angle, x, y, z));
                }
            } else if (transformElement->Name() == std::string("scale")) {
                float x, y, z;
                transformElement->QueryFloatAttribute("x", &x);
                transformElement->QueryFloatAttribute("y", &y);
                transformElement->QueryFloatAttribute("z", &z);
                transforms.push_back(std::make_unique<Scale>(x, y, z));
            }
            transformElement = transformElement->NextSiblingElement();
        }
    }

    XMLElement *modelsElement = groupElement->FirstChildElement("models");
    if (modelsElement) {
        XMLElement *modelElement = modelsElement->FirstChildElement("model");
        while (modelElement) {
            const char *file = modelElement->Attribute("file");
            if (modelBuffers.find(file) != modelBuffers.end()) {
                models.push_back(modelBuffers[file]);
            } else {
                Model model(file);
                modelBuffers[file] = model;
                models.push_back(model);
            }
            models.emplace_back(file);
            modelElement = modelElement->NextSiblingElement("model");
        }
    }

    XMLElement *subgroupElement = groupElement->FirstChildElement("group");
    while (subgroupElement) {
        subgroups.push_back(parseGroup(subgroupElement));
        subgroupElement = subgroupElement->NextSiblingElement("group");
    }

    return {std::move(transforms), std::move(models), std::move(subgroups)};
}
