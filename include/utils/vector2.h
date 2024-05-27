#ifndef CG2324_VECTOR2_H
#define CG2324_VECTOR2_H


struct Vector2
{
    float x{}, y{};

    Vector2() : x(0), y(0) {}

    Vector2(double x, double y) : x((float) x), y((float) y)  {}
};


#endif //CG2324_VECTOR2_H
