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

    std::locale::global(std::locale(""));

    initscr();

    noecho();    
    curs_set(0);

    int h, w;

    getmaxyx(stdscr, h, w);
 
    Plotter plotter(h, w);

    Evaluator e(function, plotter);

    e.plot_function();
    e.plot_axes();

    getch();

    endwin();
    return 0;


}

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

