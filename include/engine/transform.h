#ifndef CG2324_TRANSFORM_H
#define CG2324_TRANSFORM_H


#include <vector>
#include "utils/vector3.h"
#include "utils/point3.h"
#include "deps/tinyxml2.h"

namespace transform
{
    class Transform
    {
    public:
        virtual ~Transform() = default;

        virtual void apply(float time) noexcept = 0;
    };

    class Translate : public Transform
    {
    private:
        Vector3 vector;

    public:
        explicit Translate(Vector3 vector) : vector(vector) {}

        Translate(float x, float y, float z) : vector(x, y, z) {}

        explicit Translate(tinyxml2::XMLElement *transformElement);

        void apply(float time) noexcept override;
    };

    class TimedTranslate : public Transform
    {
    private:
        float time{};
        bool align{};
        bool draw{};
        std::vector<Point3> points{};
        std::vector<Point3> curve{};
        Vector3 yVector{0, 1, 0};

    public:
        TimedTranslate(float time, bool align, bool draw, std::vector<Point3> points);

        explicit TimedTranslate(tinyxml2::XMLElement *transformElement);

        void apply(float gt) noexcept override;

    private:
        [[nodiscard]] std::pair<Point3, Vector3> getGlobalCatmullRomPoint(float gt) const;

        void drawCurve() const;
    };

    class Rotate : public Transform
    {
    private:
        float angle{};
        Vector3 vector;

    public:
        Rotate(float angle, Vector3 vector) : angle(angle), vector(vector) {}

        Rotate(float angle, float x, float y, float z) : angle(angle), vector(x, y, z) {}

        explicit Rotate(tinyxml2::XMLElement *transformElement);

        void apply(float time) noexcept override;
    };

    class TimedRotate : public Transform
    {
    private:
        float anglePerSecond;
        Vector3 vector;

    public:
        TimedRotate(float time, Vector3 vector);

        TimedRotate(float time, float x, float y, float z);

        explicit TimedRotate(tinyxml2::XMLElement *transformElement);

        void apply(float gt) noexcept override;
    };

    class Scale : public Transform
    {
    private:
        float factorX{}, factorY{}, factorZ{};

    public:
        Scale(float x, float y, float z) : factorX(x), factorY(y), factorZ(z) {}

        explicit Scale(tinyxml2::XMLElement *transformElement);

        void apply(float time) noexcept override;
    };
}


#endif //CG2324_TRANSFORM_H
