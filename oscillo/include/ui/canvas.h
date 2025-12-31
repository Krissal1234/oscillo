#pragma once
#include <vector>
#include <ncurses.h>

class Canvas {
    std::vector<std::vector<wchar_t>> canvas;

public:
    Canvas(int width, int height);
    void set(int x, int y);
    void unset(int x, int y);

    void draw_ncurses();
};

