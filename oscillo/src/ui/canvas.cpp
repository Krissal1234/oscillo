#include "canvas.h"
#include <vector>
#include <ncurses.h>
#include <curses.h>

constexpr int pixmap[4][2] = {
{0x01, 0x08},
{0x02, 0x10},
{0x04, 0x20},
{0x40, 0x80}
};

constexpr wchar_t braille = 0x2800;

Canvas::Canvas(int width, int height) {
      this->canvas.resize(height);
      for(auto& v: this->canvas)
        v.resize(width);
    }

void Canvas::set(int x, int y) {
    int max_px = this->canvas[0].size() * 2;
    int max_py = this->canvas.size() * 4;
    if (x < 0 || x >= max_px || y < 0 || y >= max_py) return;

    this->canvas[y / 4][x / 2] |= pixmap[y % 4][x % 2];
}

void Canvas::unset(int x, int y) {
  if(x > (this->canvas[0].size() * 2) or x < 1) x = 0;
  if(y > (this->canvas.size() * 4) or y < 1)    y = 0;
  this->canvas[y / 4][x / 2] &= ~pixmap[y % 4][x % 2];
}

void Canvas::draw_ncurses() {
    //ncurses requires its own complex char
    cchar_t complex_char {};

    for (int row = 0; row < canvas.size(); ++row) {
        for (int col = 0; col < canvas[row].size(); ++col) {
            wchar_t c = canvas[row][col];
            if (c != 0) {
                wchar_t dot {0x2800 + c};
                setcchar(&complex_char,&dot, WA_NORMAL, 0 ,NULL);

                mvadd_wch(row,col, &complex_char);
            }
        }
    }
    refresh(); 
}


