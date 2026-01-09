cmake_minimum_required(VERSION 3.15)
project(Oscillo)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 1. Ask for the Wide version specifically
set(CURSES_NEED_WIDE TRUE) 
find_package(Curses REQUIRED)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
add_executable(oscillo
    src/main.cpp
    src/evaluator.cpp
    src/function_eval/lexical_analysis/lexer.cpp
    src/function_eval/lexical_analysis/token.cpp
    src/function_eval/syntax_analysis/syntax_tree.cpp
    src/function_eval/syntax_analysis/parser.cpp
    src/ui/plotter.cpp
    src/ui/canvas.cpp
    src/tests/evaluator_tests.cpp
)

target_compile_definitions(oscillo PRIVATE NCURSES_WIDECHAR=1)

target_include_directories(oscillo PUBLIC 
    include 
    include/lexical_analysis 
    include/syntax_analysis
    include/ui
)

target_link_libraries(oscillo ncursesw)
