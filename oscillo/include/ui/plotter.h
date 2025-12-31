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
    
    Pixel origin;
    Canvas canvas;


    Pixel map_to_pixel(double math_x, double math_y);

    void draw_axes();


public:
    Plotter(int rows, int cols, int range_x = 20);
    void plot(double x, double y);
    void plot_and_render_axes();
    void render();

    //getters
    int get_xmax();
    int get_xmin();
    int get_pcols();
    
};
