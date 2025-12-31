<div id="top"></div>

<!-- PROJECT LOGO -->
<br />
<div align="center">
  </a>

  <h3 align="center">Oscillo</h3>

  <p align="center">
    Plot mathematical functions without ever leaving the terminal!
  </p>
</div>


## About The Project

Oscillo is a C++ terminal application designed to render mathematical functions with higher quality than traditional ASCII drawings. By utilising Unicode Braille patterns, the project achieves a **2x4 sub-pixel resolution** within a single character cell, allowing for smooth curves and detailed mathematical visualisation directly in the terminal.

### Key Technical Features

* **Custom Math Engine**: Features a robust **Lexer** and **Recursive Descent Parser** that tokenises mathematical strings and transforms them into an **Abstract Syntax Tree (AST)**. This allows for efficient recursive evaluation of complex expressions.
* **High-Resolution Braille Rendering**: Instead of plotting one point per character, this project maps mathematical coordinates to a virtual bit-grid. Every 8 bits are then encoded into a specific Unicode Braille character, effectively quadrupling the vertical resolution and doubling the horizontal resolution of the terminal.
* **Bresenham's Line Algorithm**: To ensure a continuous curve without gaps, the plotter implements a customised Bresenham algorithm.

### Built With

* [C++20](https://en.cppreference.com/w/cpp/20)
* [ncurses](https://invisible-island.net/ncurses/) (for terminal window management and color support)


### Prerequisites

You will need a C++ compiler supporting C++20 and the ncurses library installed on your system.
* Ubuntu/Debian:
  ```sh
  sudo apt-get install libncurses5-dev libncursesw5-dev
  ```
