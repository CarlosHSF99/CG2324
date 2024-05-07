#include "engine/group.h"

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
