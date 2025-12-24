#pragma once

#include <vector>
#include <memory>
#include "token.h"


class Lexer {
private:
    // input and output variables
    std::string_view input_str;
    std::vector<std::unique_ptr<Token>> tokens;
    

    int curr_pos {};

    void reset();
    char peek_current();
    char peek_next();
    char advance();
    bool is_operator(char c);

public:
    Lexer(std::string_view input);
    
    void tokenise();
    void print_tokens_vector();

   


};

