
<!-- PROJECT LOGO -->
<br />
<div align="center">
  </a>


  <h3 align="center">Oscillo</h3>

  <p align="center">
    Plot mathematical functions without ever leaving the terminal!
  </p>
<img width="700" height="700" alt="Screenshot from 2026-01-09 19-03-16" src="https://github.com/user-attachments/assets/4d2ae9c4-a304-44a9-aa54-eef0c124d588" />

</div>


## About The Project

Oscillo is a C++ terminal application designed to render mathematical functions with higher quality than traditional ASCII drawings. By utilising Unicode Braille patterns, the project achieves a **2x4 sub-pixel resolution** within a single character cell, allowing for smooth curves and detailed mathematical visualisation directly in the terminal.

### Key Technical Features

* **Custom Math Engine**: Features a custom **Lexer** and **Recursive Descent Parser** that tokenises mathematical strings and transforms them into an **Abstract Syntax Tree (AST)**. This allows for recursive evaluation of different values of x, used to plot each point of the function.
* **High-Resolution Braille Rendering**: Instead of plotting one point per character, this project maps mathematical coordinates to a virtual bit-grid. Every 8 bits are then encoded into a specific Unicode Braille character where every character cell acts as a 2x4 pixel display. This effectively quadruples the vertical resolution and doubles the horizontal resolution of the terminal.
* **Bresenham's Line Algorithm**: To ensure a continuous curve without gaps, the plotter implements a customised Bresenham algorithm.
<div align="center">

### Operations & Functions

| Category | Syntax | Examples |
| :--- | :--- | :--- |
| **Arithmetic** | `+`, `-`, `*`, `/` | `x + 5`, `x / 2`, `(x + 1) * (x - 1)` |
| **Trigonometry** | `sin()`, `cos()`, `tan()` | `sin(x)`, `cos(x / 2)`, `tan(x)` |
| **Logarithms** | `log()`, `exp()` | `log(x)`, `exp(x)` |
| **Power** | `base^(exp)` | `x^(2)`, `2^(x+1)`, `(x+1)^(0.5)` |
| **Root/Misc** | `sqrt()`, `abs()` | `sqrt(x + 10)`, `abs(x)` |
| **Implicit Mult.** | `n(x)` or `(a)(b)` | `2x`, `5sin(x)`, `(x+1)(x-2)` |

> [!IMPORTANT]
> **Power Operator Requirement:** The exponent for the `^` operator must always be enclosed in parentheses. For example, use `x^(2)` instead of `x^2`.

</div>

<div align="center">
  <table border="0">
    <tr>
      <td>
        <img width="450" alt="Screenshot from 2026-01-09 21-43-39" src="https://github.com/user-attachments/assets/de56c506-92de-443a-9747-58c9f1c79cfa" />
      </td>
      <td>
        <img width="450" alt="Screenshot from 2026-01-09 21-19-04" src="https://github.com/user-attachments/assets/a82c7631-d9be-4f98-b57f-840b030f8c15" />
      </td>
    </tr>
  </table>
</div>

---

## How it Works

Oscillo transforms a simple string of text into a terminal plot through the following pipeline:

### 1. Lexical Analysis
The **Lexer** scans the raw input string and breaks it into a stream of meaningful tokens. It identifies literals, variables, operators, and function names (e.g sin, log, sqrt, etc), while also handling mathematical rules like implicit multiplication.
* **Input:** `"2x + sin(x)"`
* **Output:** `[LITERAL: 2], [VARIABLE: x], [OPERATOR: +], [FUNCTION: sin], [SEPARATOR: (], [VARIABLE: x], [SEPARATOR: )]`

### 2. Recursive Descent Parsing
The **Parser** consumes the token stream following mathematical precedence (BIDMAS). It constructs an **Abstract Syntax Tree (AST)**, a hierarchical representation of the formula. This structure allows the engine to evaluate nested expressions by recursively traversing the tree.

### 3. Coordinate Mapping & Evaluation
The **Evaluator** determines the terminal's dimensions and iterates through the horizontal range ($x$-axis). For every pixel column:
* It resolves the AST for the specific $x$ value to calculate $y$.
* It maps these mathematical coordinates ($x, y$) to the plotter's local pixel grid.
* It utilises **Bresenham's Line Algorithm** to connect these points, ensuring a continuous curve.

### 4. Braille Encoding & Rendering
Instead of standard ASCII characters, Oscillo uses **Unicode Braille patterns (U+2800 - U+28FF)** to achieve more detail.
* **Sub-pixel Resolution:** Each terminal character cell is treated as a **2x4 bit-grid**.
* **Bit Manipulation:** When a point is plotted, the corresponding bit in that cell's grid is toggled via a bitwise OR operation.
* **The Final Character:** The 8-bit grid is converted into a hex offset added to the base Braille character code. This quadruples the vertical resolution and doubles the horizontal resolution compared to traditional ASCII plotting.



---

### Built With

* [C++20](https://en.cppreference.com/w/cpp/20)
* [ncurses](https://invisible-island.net/ncurses/) (for terminal window management)


## Getting Started

### Prerequisites

You will need a C++ compiler supporting C++20 and the ncurses library installed on your system.
* Ubuntu/Debian:
  ```sh
  sudo apt-get install libncurses5-dev libncursesw5-dev
  ```
### Installation & Build

Oscillo uses a standard CMake build pipeline:

#### 1. Clone the repository
```sh
git clone https://github.com/Krissal1234/oscillo.git
cd oscillo
```
#### 2. Create build directory
```sh
mkdir build && cd build
```
#### 3. Compile
```sh
cmake ..
make
```

### Examples to Try
Run these commands to see the Braille rendering in action:
* **Wave Interference:** `./oscillo "sin(x) + cos(2x)"`
* **Discontinuities:** `./oscillo "tan(x)"` 



