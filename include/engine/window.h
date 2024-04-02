#ifndef CG2324_WINDOW_H
#define CG2324_WINDOW_H


class Window
{
public:
    int width, height;
    char *title;

public:
    Window() = default;

    Window(int width, int height, char *title) : width(width), height(height), title(title) {};
};


#endif //CG2324_WINDOW_H
