#include "lexer.h"
#include "token_factory.h"
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

std::vector<std::unique_ptr<Token>> Lexer::get_tokens() {
    return std::move(tokens);
}
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


void Lexer::print_tokens_vector() {
    for (const auto& token : tokens) {
        if (token) {
            token->print();
        }
    }
}

// void Lexer::preprocess_input() {
//
// }


void Lexer::handle_digit(char c) {

    std::string digit_string {c};

    while (std::isdigit(peek_current())) {
        digit_string += advance();
    }

    tokens.push_back(TokenFactory::create_operand(TokenType::LITERAL, stoi(digit_string)));
}

void Lexer::tokenise() {
    char c = peek_current(); //just peeks, does not move pointer yet
    
    while (c != '\0') {
        c = advance();

        //Operator Check
        std::unordered_map<char,OperatorType>::const_iterator got = operator_list.find(c);
        if (got != operator_list.end()) {
            tokens.push_back(TokenFactory::create_operator(got->second));
            continue;
        }

        //Operand check
        if (c == 'x') {
            tokens.push_back(TokenFactory::create_operand(TokenType::VARIABLE, 0));
        }

        if (c == '(' || c == ')') {
            tokens.push_back(TokenFactory::create_seperator(c));
        }

        //handle digit handles advances 
        if (std::isdigit(c)) {
            handle_digit(c);
            continue;
        }
    }

    //constant folding
}




