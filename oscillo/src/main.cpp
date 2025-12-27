#include <iostream>
#include <string>
#include <sstream>
#include <cstdlib>
#include <sys/ioctl.h>
// #include <unistd.h>
// #include <ncurses.h>
#include "lexer.h"


/*
 *
 *input from cin is a functtion in string format
 it will pass through a lexer that will put it in a token format e.g. {NUMBER, 2.5}
 Then a parser will build an AST tree. this will make it easy to evaluate the function
 once the tree is build we can easily evaluate for multiple values of x

 Then we can use ncurser to plot, this will be difficult
 *
 *
 *
// */


std::string split(const std::string& str);
std::string extract_from_args(int argc, char **argv);

int main(int argc, char **argv) {

    std::string function {};

    if (argc >= 5) {
        std::cout << "Too many arguments, Tip: dont use whitespaces" << std::endl;
    }

    //extract function std::string, either through splitting a single string or through multiple function arguments
    if (argc == 2) { //one argument so possibly contains double brackets to contain function""
        function = split(argv[1]);
    } else {
        function = extract_from_args(argc, argv);
    }

    std::cout << "Function: " << function << '\n';

    
    Lexer lexer(function);

    lexer.tokenise();

    lexer.print_tokens_vector();
    



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

