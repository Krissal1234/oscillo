#include <iostream>
#include "token.h"


Token::Token(TokenType tok_type) : tok_type(tok_type) {};

OperatorToken::OperatorToken(OperatorType op_type) : Token(TokenType::OPERATOR), op_type(op_type) {};

OperatorType OperatorToken::get_operator_type() const {
    return op_type;
}
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

SeperatorToken::SeperatorToken(SeperatorType sep_type) : Token(TokenType::SEPERATOR), sep_type(sep_type) {};

SeperatorType SeperatorToken::get_seperator_type() const {
    return sep_type;
}

void SeperatorToken::print() const {
    switch(sep_type) {
        case SeperatorType::OPEN_BRACKET:            std::cout << "[ ( ]" << '\n'; break;
        case SeperatorType::CLOSE_BRACKET:           std::cout << "[ ) ]" << '\n'; break;
    default:                                std::cout << "[]";
}
}

FunctionToken::FunctionToken(FunctionType func_type) : Token(TokenType::FUNCTION), func_type(func_type) {};

FunctionType FunctionToken::get_func_type() const {
    return func_type;
}
void FunctionToken::print() const {
    std::cout << "[FUNCTION] - ";
    switch(func_type) {
        case FunctionType::SIN:   std::cout << "[sin]"; break;
        case FunctionType::COS:   std::cout << "[cos]"; break;
        case FunctionType::TAN:   std::cout << "[tan]"; break;
        case FunctionType::LOG:   std::cout << "[log]"; break;
        case FunctionType::SQRT:  std::cout << "[sqrt]"; break;
        case FunctionType::COSEC:  std::cout << "[cosec]"; break;
        default:                  std::cout << "[unknown]"; break;
    }
    std::cout << '\n';
}
