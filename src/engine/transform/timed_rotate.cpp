#include <GL/glut.h>
#include "deps/tinyxml2.h"
#include "engine/transform.h"

using namespace tinyxml2;

namespace transform
{
    TimedRotate::TimedRotate(XMLElement *transformElement)
    {
        float time;
        transformElement->QueryFloatAttribute("time", &time);
        anglePerSecond = (bool) time ? 360.0f / time : 0;
        vector = Vector3(transformElement);
    }

    TimedRotate::TimedRotate(float time, Vector3 vector) : vector(vector)
    {
        anglePerSecond = (bool) time ? 360.0f / time : 0;
    }

    TimedRotate::TimedRotate(float time, float x, float y, float z) : vector(x, y, z)
    {
        anglePerSecond = (bool) time ? 360.0f / time : 0;
    }

    void TimedRotate::apply(float gt) noexcept
    {
        glRotatef(gt * anglePerSecond, vector.x, vector.y, vector.z);
    }
}
