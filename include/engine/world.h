#ifndef CG2324_WORLD_H
#define CG2324_WORLD_H


#include <utility>

#include "engine/group.h"
#include "engine/camera.h"
#include "engine/window.h"

class World
{
public:
    Window window{};
    Camera camera;
    Group group;

public:
    World() = default;

    explicit World(Window window, Camera camera, Group group) :
            window(window), camera(std::move(camera)), group(std::move(group)) {}

    void draw() const;
};


#endif //CG2324_WORLD_H
