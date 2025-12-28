cmake_minimum_required(VERSION 3.15)
project(Oscillo)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add the executable
add_executable(oscillo
    src/main.cpp
    src/function_eval/evaluator.cpp

    src/function_eval/lexical_analysis/lexer.cpp
    src/function_eval/lexical_analysis/token.cpp

    src/function_eval/syntax_analysis/syntax_tree.cpp
    src/function_eval/syntax_analysis/parser.cpp

    src/ui/canvas.cpp

    src/tests/evaluator_tests.cpp
    
)

# Include the header folder
target_include_directories(oscillo PUBLIC 
    include 
    include/lexical_analysis 
    include/syntax_analysis
    include/ui
)

find_package(Curses REQUIRED)

# 2. Include the directories where the header files are
include_directories(${CURSES_INCLUDE_DIRS})

# 3. Link the library to your executable
target_link_libraries(oscillo ${CURSES_LIBRARIES})
