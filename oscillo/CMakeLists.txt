cmake_minimum_required(VERSION 3.15)
project(Oscillo)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add the executable
add_executable(oscillo
    src/main.cpp
    src/evaluator.cpp

    src/lexical_analysis/lexer.cpp
    src/lexical_analysis/token.cpp

    src/syntax_analysis/syntax_tree.cpp
    src/syntax_analysis/parser.cpp

    src/tests/evaluator_tests.cpp
)

# Include the header folder
target_include_directories(oscillo PUBLIC 
    include 
    include/lexical_analysis 
    include/syntax_analysis
)
