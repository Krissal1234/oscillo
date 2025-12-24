#include <iostream>
#include "lexer.h"
#include <memory>
#include <unordered_map>

// static constexpr std::string_view operator_list {"+/-*"};

static const std::unordered_map<char, OperatorType> operator_list {
    {'+', OperatorType::ADDITION}, 
    {'/', OperatorType::DIVISION},
    {'-', OperatorType::SUBTRACTION},
    {'*', OperatorType::MULTIPLICATION}
};

// Constructor
Lexer::Lexer(std::string_view input) : input_str(input) {};

// Lexer commands
char Lexer::advance() {
    char current = peek_current();

    if (current != '\0') {
        curr_pos++;
    } 

    return current;
}

char Lexer::peek_current() {
    if (curr_pos >= input_str.length()) {return '\0';}

    return input_str[curr_pos];
}

char Lexer::peek_next() {
    if (curr_pos + 1 >= input_str.length()) {return '\0';}

    return input_str[curr_pos + 1];
}

void Lexer::reset() {
    curr_pos = 0;
}

void Lexer::print_tokens_vector() {
    for (const auto& token : tokens) {
        if (token) {
            token->print();
        }
    }
}



void Lexer::tokenise() {
    char c = peek_current(); 
    std::string digit_string {}; 

    while (c != '\0') {
        c = advance();

        //Operator Check
        std::unordered_map<char,OperatorType>::const_iterator got = operator_list.find(c);
        if (got != operator_list.end()) {
            tokens.push_back(std::make_unique<OperatorToken>(got->second));
        }

        //Operand check
        // Variable Check
        if (c == 'x') {
            //This is the actual variable we will modify
            tokens.push_back(std::make_unique<OperandToken>(TokenType::VARIABLE, 0));
        }

        // Literal Check
        if (std::isdigit(c)) {
            digit_string += c;
            if (!std::isdigit(peek_current())) {
                tokens.push_back(std::make_unique<OperandToken>(TokenType::LITERAL, std::stoi(digit_string)));

                digit_string.clear();
            }
        }
    }
}




