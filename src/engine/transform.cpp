#include <array>
#include <cmath>
#include <GL/glut.h>
#include "engine/transform.h"

std::pair<Point3, Vector3> getCatmullRomPoint(float t, Point3 p0, Point3 p1, Point3 p2, Point3 p3);

std::array<float, 16> buildRotationMatrix(Vector3 x, Vector3 y, Vector3 z);

TimedTranslate::TimedTranslate(float time, bool align, bool draw, std::vector<Point3> points)
        : time(time), align(align), draw(draw), points(std::move(points))
{
    float gt = 0.0f;
    const unsigned long nSteps = this->points.size() * 100;
    const float tStep = time / (float) nSteps;

    for (int i = 0; i < nSteps; i++) {
        curve.push_back(getGlobalCatmullRomPoint(gt).first);
        gt += tStep;
    }
}

TimedRotate::TimedRotate(float time, Vector3 vector) : vector(vector)
{
    anglePerSecond = (bool) time ? 360.0f / time : 0;
}

TimedRotate::TimedRotate(float time, float x, float y, float z) : vector(x, y, z)
{
    anglePerSecond = (bool) time ? 360.0f / time : 0;
}

void Translate::apply(float) noexcept
{
    glTranslatef(this->vector.x, this->vector.y, this->vector.z);
}

void Rotate::apply(float) noexcept
{
    glRotatef(this->angle, this->vector.x, this->vector.y, this->vector.z);
}

void Scale::apply(float) noexcept
{
    glScalef(this->factorX, this->factorY, this->factorZ);
}

void TimedTranslate::apply(float gt) noexcept
{
    if (draw) {
        drawCurve();
    }

    auto [pos, dir] = getGlobalCatmullRomPoint(gt);
    glTranslatef(pos.x, pos.y, pos.z);

    if (align) {
        Vector3 x = Vector3::normalize(dir); // x could be omitted and use dir directly
        Vector3 z = Vector3::normalize(Vector3::cross(x, yVector));
        yVector = Vector3::normalize(Vector3::cross(z, x));

        glMultMatrixf(buildRotationMatrix(x, yVector, z).data());
    }
}

void TimedRotate::apply(float gt) noexcept
{
    glRotatef(gt * anglePerSecond, vector.x, vector.y, vector.z);
}

std::pair<Point3, Vector3> TimedTranslate::getGlobalCatmullRomPoint(float gt) const
{
    int pointCount = (int) points.size();
    float t = gt / time * (float) pointCount; // this is the real global t
    int index = std::floor(t); // which segment
    t = t - (float) index; // where within  the segment

    // indices store the points
    int indices[4];
    indices[0] = (index + pointCount - 1) % pointCount;
    indices[1] = (indices[0] + 1) % pointCount;
    indices[2] = (indices[1] + 1) % pointCount;
    indices[3] = (indices[2] + 1) % pointCount;

    return getCatmullRomPoint(t, points[indices[0]], points[indices[1]], points[indices[2]], points[indices[3]]);
}

void TimedTranslate::drawCurve() const
{
    glBegin(GL_LINE_LOOP);
    for (const auto &point: curve) {
        glVertex3f(point.x, point.y, point.z);
    }
    glEnd();
}

std::pair<Point3, Vector3> getCatmullRomPoint(float t, Point3 p0, Point3 p1, Point3 p2, Point3 p3)
{
    // catmull-rom matrix
    static const float m[4][4]{
            {-0.5f, +1.5f, -1.5f, +0.5f},
            {+1.0f, -2.5f, +2.0f, -0.5f},
            {-0.5f, +0.0f, +0.5f, +0.0f},
            {+0.0f, +1.0f, +0.0f, +0.0f},
    };

    // point matrix
    const float p[4][3]{
            {p0.x, p0.y, p0.z},
            {p1.x, p1.y, p1.z},
            {p2.x, p2.y, p2.z},
            {p3.x, p3.y, p3.z},
    };

    const float tv[4] = {powf(t, 3), powf(t, 2), t, 1};
    const float tvd[4] = {3 * powf(t, 2), 2 * t, 1, 0};

    float pv[3] = {0};
    float dv[3] = {0};

    for (int i = 0; i < 3; i++) {
        float a[4] = {0};
        for (int j = 0; j < 4; j++) {
            for (int k = 0; k < 4; k++) {
                a[j] += m[j][k] * p[k][i];
            }
        }
        for (int j = 0; j < 4; j++) {
            pv[i] += tv[j] * a[j];
            dv[i] += tvd[j] * a[j];
        }
    }

    return {{pv[0], pv[1], pv[2]},
            {dv[0], dv[1], dv[2]}};
}

std::array<float, 16> buildRotationMatrix(Vector3 x, Vector3 y, Vector3 z)
{
    return {
            x.x, x.y, x.z, 0,
            y.x, y.y, y.z, 0,
            z.x, z.y, z.z, 0,
            0, 0, 0, 1,
    };
}
