#pragma once
#include <vector>
#include <memory>
#include "token.h"


class Lexer {
private:
    // input and output variables
    std::string_view input_str;
    std::vector<std::unique_ptr<Token>> tokens;
    

    int curr_pos {0};

    void reset();
    char peek_current();
    char peek_next();
    char advance();
    bool is_operator(char c);
    double handle_digit(char c);
    void handle_alpha(char c);
    bool needs_implicit_multiplication(char current_c);

public:
    Lexer(std::string_view input);
    std::vector<std::unique_ptr<Token>> get_tokens();
    
    void tokenise();
    void print_tokens_vector();

   


};

