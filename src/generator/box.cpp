#include <cmath>
#include "generator/plane.h"
#include "generator/box.h"

using std::vector;

vector<Model> createBox(float size, int divisions);

Box::Box(float size, int divisions) : Model(createBox(size, divisions)) {}

vector<Model> createBox(float size, int divisions)
{
    float halfSize = size / 2;

    Plane top(size, divisions);
    top.translate({0, halfSize, 0});
    Plane bottom(size, divisions);
    bottom.rotate({0, 0, 1}, M_PI);
    bottom.translate({0, -halfSize, 0});
    Plane left(size, divisions);
    left.rotate({0, 1, 0}, M_PI_2); // unnecessary, just to match diagonals in professor's example
    left.rotate({0, 0, 1}, M_PI_2);
    left.translate({-halfSize, 0, 0});
    Plane right(size, divisions);
    right.rotate({0, 1, 0}, M_PI_2); // unnecessary, just to match diagonals in professor's example
    right.rotate({0, 0, 1}, -M_PI_2);
    right.translate({halfSize, 0, 0});
    Plane front(size, divisions);
    front.rotate({0, 1, 0}, M_PI_2); // unnecessary, just to match diagonals in professor's example
    front.rotate({1, 0, 0}, M_PI_2);
    front.translate({0, 0, halfSize});
    Plane back(size, divisions);
    back.rotate({0, 1, 0}, M_PI_2); // unnecessary, just to match diagonals in professor's example
    back.rotate({1, 0, 0}, -M_PI_2);
    back.translate({0, 0, -halfSize});

    return vector<Model>{top, bottom, left, right, front, back};
}
