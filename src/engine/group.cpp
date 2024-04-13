#include <GL/glut.h>
#include "engine/group.h"

void Group::draw() const
{
    glPushMatrix();

    for (const auto &transform: this->transforms) {
        transform->apply();
    }

    for (const auto &model: this->models) {
        model.draw();
    }

    for (const auto &group: this->subgroups) {
        group.draw();
    }

    glPopMatrix();
}
