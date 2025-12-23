cmake_minimum_required(VERSION 3.15)
project(Oscillo)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add the executable
add_executable(oscillo
    src/main.cpp
    src/evaluator/evaluator.cpp
    src/evaluator/lexer.cpp
    src/evaluator/token.cpp
)

# Include the header folder
target_include_directories(oscillo PUBLIC include)
