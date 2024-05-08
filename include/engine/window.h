#ifndef CG2324_WINDOW_H
#define CG2324_WINDOW_H


#include "deps/tinyxml2.h"

class Window
{
public:
    int x{}, y{};
    int width{}, height{};

public:
    Window() = default;

    Window(int x, int y, int width, int height) : x(x), y(y), width(width), height(height) {};

    explicit Window(tinyxml2::XMLElement *windowElement);
};


#endif //CG2324_WINDOW_H
