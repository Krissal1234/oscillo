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
    bool has_prev;
    Pixel prev_p;
    

    Pixel map_to_pixel(double math_x, double math_y);

    void draw_axes();

public:
    Plotter(int rows, int cols, double range_x = 15.0);
    void plot(double x, double y);
    void plot_and_render_axes();
    void draw_line(int x0, int y0, int x1, int y1);
    void render();

    double get_xmax();
    double get_xmin();
    double get_pcols();
    
};
