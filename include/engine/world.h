#ifndef CG2324_WORLD_H
#define CG2324_WORLD_H


#include "engine/group.h"
#include "engine/camera.h"
#include "deps/tinyxml2.h"

class World
{
public:
    Camera camera;
    Group group;

public:
    World() = default;

    World(Camera camera, Group group) : camera(std::move(camera)), group(std::move(group)) {}

    explicit World(tinyxml2::XMLElement *worldElement);

    void renderScene();

    void changeSize(int w, int h) const;

    void processNormalKeys(unsigned char key, int xx, int yy);
};


#endif //CG2324_WORLD_H
