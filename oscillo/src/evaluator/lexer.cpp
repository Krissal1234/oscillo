#include <iostream>
#include "lexer.h"

static const std::string operator_list {"+/-*"};


// Constructor
Lexer::Lexer(std::string input) : input_str(input) {};

// Lexer commands
char Lexer::advance() {
    char current = peek();

    if (current != '\0') {
        curr_pos++;
    } 

    return current;
}

char Lexer::peek() {
    if (curr_pos >= input_str.length()) {return '\0';}

    return input_str[curr_pos];
}

void Lexer::reset() {
    curr_pos = 0;
}

bool Lexer::is_operator(char c) {
    return operator_list.find(c) != std::string::npos;
}


void Lexer::tokenise() {
    char c = peek(); 

    while (c != '\0') {
        c = advance();

        if (is_operator(c)) {

        }

        if (std::isdigit(c)) {
            std::cout << "foujnd digit" << '\n';
        }
        //tokenising logic

    }
}




