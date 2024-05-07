#ifndef CG2324_WINDOW_H
#define CG2324_WINDOW_H


class Window
{
public:
    int x, y;
    int width, height;
    char *title;

public:
    Window() = default;

    Window(int x, int y, int width, int height, char *title)
            : x(x), y(y), width(width), height(height), title(title) {};
};


#endif //CG2324_WINDOW_H
