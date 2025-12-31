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
    double y_min;
    double y_max;
    double x_min;
    double x_max;

    double range_x;
    
    Pixel origin;
    Canvas canvas;


    Pixel map_to_pixel(double math_x, double math_y);

    void draw_axes();


public:
    Plotter(int rows, int cols, double range_x = 20.0);
    void plot(double x, double y);
    void plot_and_render_axes();
    void render();

    //getters
    double get_xmax();
    double get_xmin();
    double get_pcols();
    
};
