#pragma once
#include "token.h"
#include "syntax_tree.h"
#include <memory>
#include <vector>


class Parser {
    std::vector<std::unique_ptr<Token>> tokens;
    int pos {0};

    Token* peek(); //we return a pointer and not a ref since we can check for a nullptr to denote end of tokens

    Token* advance();

    std::unique_ptr<Node> parse_factor(); //multiplication or division 
    std::unique_ptr<Node> parse_term(); // indices
public:
    std::unique_ptr<Node> parse_expression(); //returns root 
    
    Parser(std::vector<std::unique_ptr<Token>> tokens);

};

