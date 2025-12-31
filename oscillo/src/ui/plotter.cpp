#include "plotter.h" 
#include "canvas.h"
#include <ncurses.h>
#include <cmath>


Plotter::Plotter(int rows, int cols, int range_x) 
    : rows(rows), cols(cols), p_rows(rows * 4), p_cols(cols * 2), range_x(range_x) 
{
    double range_y = range_x * ((double)p_rows / (double)p_cols) * 0.5; //range_y determined dynamically

    this->x_min = -range_x / 2.0;
    this->x_max =  range_x / 2.0;
    this->y_min = -range_y / 2.0;
    this->y_max =  range_y / 2.0;
}


Pixel Plotter::map_to_pixel(double math_x, double math_y) {
    // 1. Calculate percentage across the math plane
    double px_pct = (math_x - x_min) / (x_max - x_min);
    double py_pct = (y_max - math_y) / (y_max - y_min);

    // 2. Multiply by (pixels - 1) to stay within array bounds [0, p_cols-1]
    int px = static_cast<int>(px_pct * (p_cols - 1));
    int py = static_cast<int>(py_pct * (p_rows - 1));

    bool visible = (px >= 0 && px < p_cols && py >= 0 && py < p_rows);

    return {px, py, visible};
}


void Plotter::draw_function() {
    Canvas canvas(cols, rows);

    Pixel origin = map_to_pixel(0.0, 0.0);

    if (origin.y >= 0 && origin.y < p_rows) {
        for (int x = 0; x < p_cols; ++x) {
            canvas.set(x, origin.y);
        }
    }

    if (origin.x >= 0 && origin.x < p_cols) {
        for (int y = 0; y < p_rows; ++y) {
            canvas.set(origin.x, y);
        }
    }

    double math_width = x_max - x_min;
    double step = math_width / p_cols; 

    for (int i = 0; i < p_cols; ++i) {
        double math_x = x_min + (i * step);
        double math_y = std::sin(math_x); 
        
        Pixel p = map_to_pixel(math_x, math_y);
        if (p.on_screen) {
            canvas.set(p.x, p.y);
        }
    }

    canvas.draw_ncurses();
    refresh(); 
}






