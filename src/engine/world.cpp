#include <GL/glut.h>
#include "engine/world.h"

void World::draw() const
{
    group.draw((float) glutGet(GLUT_ELAPSED_TIME) / 1000.0f);
}
