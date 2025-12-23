#pragma once
#include <string>


enum class TokenType {VARIABLE, NUMBER, OPERATOR, PAREN};

class Token {
    TokenType type;
    std::string value;
public:
    template<typename T>
    Token(TokenType type, T value);
};
