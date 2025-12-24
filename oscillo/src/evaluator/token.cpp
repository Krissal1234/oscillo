#include <iostream>
#include "token.h"


Token::Token(TokenType tok_type) : tok_type(tok_type) {};

OperatorToken::OperatorToken(OperatorType op_type) : Token(TokenType::OPERATOR), op_type(op_type) {};

void OperatorToken::print() const {
    switch(op_type) {
        case OperatorType::ADDITION:       std::cout << "[+]" << '\n'; break;
        case OperatorType::SUBTRACTION:    std::cout << "[-]" << '\n'; break;
        case OperatorType::MULTIPLICATION: std::cout << "[*]" << '\n'; break;
        case OperatorType::DIVISION:       std::cout << "[/]" << '\n'; break;
        default:                           std::cout << "[?]" << '\n'; break;
    }
}
OperandToken::OperandToken(TokenType tok_type, double value) : Token(tok_type), value(value) {};

void OperandToken::print() const {
    switch(tok_type) {
        case TokenType::LITERAL:            std::cout << "[LITERAL] - "; break;
        case TokenType::VARIABLE:           std::cout << "[VARIABLE] - "; break;
    default:                                std::cout << "[]";
}
    std::cout << "[" << value << "]" << '\n';

}


