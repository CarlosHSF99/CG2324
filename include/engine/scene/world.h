#ifndef CG2324_WORLD_H
#define CG2324_WORLD_H


#include "deps/tinyxml2.h"
#include "group.h"
#include "camera.h"
#include "light.h"

class World
{
public:
    Camera camera;
    std::vector<std::unique_ptr<Light>> lights;
    Group group;

    // draw options
    bool axis{};

public:
    World() = default;

    World(Camera camera, Group group) : camera(std::move(camera)), group(std::move(group)) {}

    explicit World(tinyxml2::XMLElement *worldElement);

    void renderScene();

    void changeSize(int w, int h) const;

    void processNormalKeys(unsigned char key, int xx, int yy);
};


#endif //CG2324_WORLD_H
