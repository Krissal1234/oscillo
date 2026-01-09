#pragma once
#include "token.h"
#include <memory>


class TokenFactory {
public:
    static std::unique_ptr<Token> create_operator(OperatorType op_type) {
        return std::make_unique<OperatorToken>(op_type);
    }
    static std::unique_ptr<Token> create_operand(TokenType tok_type, double value) {
        return std::make_unique<OperandToken>(tok_type, value);
    }
    static std::unique_ptr<Token> create_seperator(char c) {
        SeperatorType type = (c == '(') ? SeperatorType::OPEN_BRACKET : SeperatorType::CLOSE_BRACKET; 
        return std::make_unique<SeperatorToken>(type);
    }
    static std::unique_ptr<Token> create_function(FunctionType func_type) {
        return std::make_unique<FunctionToken>(func_type);
    }

};

