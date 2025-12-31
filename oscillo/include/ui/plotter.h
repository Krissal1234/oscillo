#pragma once
#include "canvas.h"



struct Pixel {
    int x,y;
    bool on_screen;
};

class Plotter{
private:
    int rows;
    int cols;

    //num of rows including writeable pixels
    int p_rows; 
    int p_cols;

    //terminal bounds
    int y_min;
    int y_max;
    int x_min;
    int x_max;

    int range_x;


    Pixel map_to_pixel(double math_x, double math_y);
    void draw_axes(Canvas& canvas);


public:
    Plotter(int rows, int cols, int range_x = 20);
    void draw_function();
};
