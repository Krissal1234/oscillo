#pragma once

#include <vector>
#include <string>
#include "token.h"


class Lexer {
private:
    // input and output variables
    std::string input_str;
    std::vector<Token> tokens;

    int curr_pos {};

    void reset();
    char peek();
    char advance();
    bool is_operator(char c);

public:
    Lexer(std::string input);
    
    void tokenise();

   


};

