
<!-- PROJECT LOGO -->
<br />
<div align="center">
  </a>


  <h3 align="center">Oscillo</h3>

  <p align="center">
    Plot mathematical functions without ever leaving the terminal!
  </p>
    <img width="700" height="700" alt="Screenshot from 2025-12-31 20-03-58" src="https://github.com/user-attachments/assets/f3df2d4d-8a55-44f1-a899-c2901459a103" />

</div>


## About The Project

Oscillo is a C++ terminal application designed to render mathematical functions with higher quality than traditional ASCII drawings. By utilising Unicode Braille patterns, the project achieves a **2x4 sub-pixel resolution** within a single character cell, allowing for smooth curves and detailed mathematical visualisation directly in the terminal.

### Key Technical Features

* **Custom Math Engine**: Features a robust **Lexer** and **Recursive Descent Parser** that tokenises mathematical strings and transforms them into an **Abstract Syntax Tree (AST)**. This allows for efficient recursive evaluation of complex expressions.
* **High-Resolution Braille Rendering**: Instead of plotting one point per character, this project maps mathematical coordinates to a virtual bit-grid. Every 8 bits are then encoded into a speci
fic Unicode Braille character, effectively quadrupling the vertical resolution and doubling the horizontal resolution of the terminal.
* **Bresenham's Line Algorithm**: To ensure a continuous curve without gaps, the plotter implements a customised Bresenham algorithm.
<div align="center">
  <table border="0">
    <tr>
      <td>
        <img src="https://github.com/user-attachments/assets/649fe279-1964-4334-9cfe-3cefb2e3fc0d" width="450" alt="Screenshot 1">
      </td>
      <td>
        <img src="https://github.com/user-attachments/assets/9ce31f41-59ac-4c17-83a4-3da843e96a1a" width="450" alt="Screenshot 2">
      </td>
    </tr>
  </table>
</div>

### Built With

* [C++20](https://en.cppreference.com/w/cpp/20)
* [ncurses](https://invisible-island.net/ncurses/) (for terminal window management and color support)


### Prerequisites

You will need a C++ compiler supporting C++20 and the ncurses library installed on your system.
* Ubuntu/Debian:
  ```sh
  sudo apt-get install libncurses5-dev libncursesw5-dev
  ```
