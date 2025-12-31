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
Lexer::Lexer(std::string_view input) : input_str(input) {
    tokens.reserve(input.length());
};

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

void Lexer::handle_digit(char c) {

    std::string digit_string {c};

    while (true) {
        char curr = peek_current();

        if (std::isdigit(curr) || curr == '.') {
            digit_string += advance();
        } else {
            break;
        }
    }

    tokens.push_back(TokenFactory::create_operand(TokenType::LITERAL, stod(digit_string)));
}

void Lexer::tokenise() {
    char c = peek_current(); //just peeks, does not move pointer yet
    
    while (c != '\0') {

        c = advance();
        
        if (std::isspace(c)) continue;

        //Operator Check
        std::unordered_map<char,OperatorType>::const_iterator got = operator_list.find(c);
        if (got != operator_list.end()) {
            tokens.push_back(TokenFactory::create_operator(got->second));
            continue;
        }

        //Operand check
        if (c == 'x') {
            tokens.push_back(TokenFactory::create_operand(TokenType::VARIABLE, 0.0));
            continue;
        }

        if (c == '(' || c == ')') {
            tokens.push_back(TokenFactory::create_seperator(c));
            continue;
        }

        //handle digit handles advances 
        if (std::isdigit(c) || c == '.') {
            handle_digit(c);
            continue;
        }

        //if code reaches here, we must have an invalid token, the check is to make account for advance() edge case
        if (c != '\0') throw std::runtime_error("Invalid Token");

    }

    //constant folding
}




