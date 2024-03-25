#include <GL/glut.h>
#include "engine/transform.h"

void Translate::apply() const noexcept
{
    glTranslatef(this->vector.x, this->vector.y, this->vector.z);
}

void Rotate::apply() const noexcept
{
    glRotatef(this->angle, this->vector.x, this->vector.y, this->vector.z);
}

void Scale::apply() const noexcept
{
    glScalef(this->factorX, this->factorY, this->factorZ);
}
