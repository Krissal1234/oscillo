#include "plotter.h" 
#include "canvas.h"
#include <ncurses.h>
#include <cmath>

static constexpr double buffer_pct = 0.05;
constexpr double aspect_ratio {0.5}; // each character is twice as wide as it is tall, so y axis needs to account 

Plotter::Plotter(int rows, int cols, double range_x) 
    : rows(rows), cols(cols), p_rows(rows * 4), p_cols(cols * 2), range_x(range_x), canvas(cols,rows)
{
    double range_y = this->range_x * static_cast<double>(p_rows) / static_cast<double>(p_cols) * aspect_ratio; //range_y determined dynamically
    this->x_min = -this->range_x / 2.0;
    this->x_max =  this->range_x / 2.0;
    this->y_min = -range_y / 2.0;
    this->y_max =  range_y / 2.0;

    this->origin = map_to_pixel(0.0,0.0);
}


Pixel Plotter::map_to_pixel(double math_x, double math_y) {
    
    if (std::isnan(math_y) || std::isinf(math_y) || std::isnan(math_x) || std::isinf(math_x)) {
        return {0, 0, false}; // Mark as not on screen
    }
    double px_pct = (math_x - x_min) / (x_max - x_min);
    double py_pct = (y_max - math_y) / (y_max - y_min);


    int px = static_cast<int>(px_pct * (p_cols - 1));
    int py = static_cast<int>(py_pct * (p_rows - 1));

    bool visible = (px >= 0 && px < p_cols && py >= 0 && py < p_rows);

    return {px, py, visible};
}


void Plotter::plot_and_render_axes() {
    if (origin.y >= 0 && origin.y < p_rows) {
        for (int x = 0; x <= p_cols; ++x) {
            canvas.set(x, origin.y);
        }
    }
    if (origin.x >= 0 && origin.x < p_cols) {
        for (int y = 0; y <= p_rows; ++y) {
            canvas.set(origin.x, y);
        }
    }

    render();
}

//implementation of Bresenham's Line Algorithm
void Plotter::draw_line(int x0, int y0, int x1, int y1) {
    int dx = std::abs(x1 - x0);
    int dy = -std::abs(y1 - y0); 

    //steps, if the endpoint is to the right, it is 1, and -1 to the left
    //tells it to increment or decrement during steps
    int sx = x0 < x1 ? 1 : -1;  
    int sy = y0 < y1 ? 1 : -1; 

    //balance, tracks how far the current point is from a smooth line
    int err = dx + dy;

    while (true) { //loop until we reach endpoint
        canvas.set(x0, y0); 

        if (x0 == x1 && y0 == y1) break;

        int e2 = 2 * err;
        if (e2 >= dy) { 
            err += dy;
            x0 += sx;
        }
        if (e2 <= dx) { 
            err += dx;
            y0 += sy;
        }
    }
}

void Plotter::plot(double x, double y) {
    Pixel current_p = map_to_pixel(x, y);


    if (!current_p.on_screen) {
        has_prev = false; 
        return;
    }

    if (has_prev) {
        if (std::abs(current_p.y - prev_p.y) < (p_rows * 0.8) 
            && std::abs(current_p.x - prev_p.x) < (p_cols * 0.8)) { //checkkng if big jump
             draw_line(prev_p.x, prev_p.y, current_p.x, current_p.y);
        }
    } else {
        canvas.set(current_p.x, current_p.y);
    }

    prev_p = current_p;
    has_prev = true;
}

void Plotter::reset_plot_state() {
    has_prev = false;
}

void Plotter::render() {
    canvas.draw_ncurses();
    refresh(); 
}

double Plotter::get_xmax() {
    return x_max;
}

double Plotter::get_xmin() {
    return x_min;
}

double Plotter::get_pcols() {
    return p_cols;
}





