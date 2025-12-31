#define _XOPEN_SOURCE_EXTENDED 1 
#include <clocale>              
#include <ncurses.h>            
#include <iostream>              
#include <string>
#include <sstream>
#include <cstdlib>
#include <sys/ioctl.h>
#include <unistd.h>
#include "evaluator.h"
#include "plotter.h"

void run_evaluator_tests();
std::string split(const std::string& str);
std::string extract_from_args(int argc, char **argv);

int main(int argc, char **argv) {
    std::locale::global(std::locale(""));

    initscr();

    if (argc >= 5) {
        std::cout << "Too many arguments, Tip: dont use whitespaces" << std::endl;
    }

    if (argc > 1 && std::string(argv[1]) == "--test") {
        run_evaluator_tests();
        return 0;
    }

    std::string function {};

    if (argc == 2) { //one argument so possibly contains double brackets to contain function""
        function = split(argv[1]);
    } else {
        function = extract_from_args(argc, argv);
    }

    noecho();    
    curs_set(0);

    int h, w;

    getmaxyx(stdscr, h, w);
 
    Plotter plotter(h, w);

    Evaluator e(function, plotter);

    e.plot_axes();
    // e.plot_function();


    getch();

    endwin();
    return 0;


}

    
    //ncursers stuff

  //   struct winsize w;
  //   ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
  //
  //   int rows = w.ws_row;
  //   int cols = w.ws_col;
  //   std::cout << "grid: " << rows << " X " << cols << '\n';
  //
  // while (1){
  //
  //   // std::cout << "Rows: " << rows << ", Columns: " << cols << std::endl;
  //
  // }




std::string split(const std::string& str) {
  std::string result;
  std::stringstream iss(str);
  std::string token;

  while (iss >> token) {
    result += token;
  }
  return result;
}

std::string extract_from_args(int argc, char **argv) {
    std::string function{};

    int i {1};

    while (i < argc) {
        function += argv[i];
        i++;
    }

    return function;
}

