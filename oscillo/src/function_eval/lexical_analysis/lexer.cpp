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


bool Lexer::needs_implicit_multiplication(char current_c) {
    if (tokens.empty()) return false;

    TokenType last_type = tokens.back()->get_tok_type();
    
    bool last_was_close_bracket = false;

    if (last_type == TokenType::SEPERATOR) {
        auto sep = static_cast<SeperatorToken*>(tokens.back().get());
        if (sep->get_seperator_type() == SeperatorType::CLOSE_BRACKET) {
            last_was_close_bracket = true;
        }
    }

    // Case 1: 2x or (x)x or xx
    if (current_c == 'x') {
        return (last_type == TokenType::LITERAL || 
                last_type == TokenType::VARIABLE ||
                last_was_close_bracket);
    }

    // Case 2: 2(x) or x(x) or (x)(x)
    if (current_c == '(') {
        return (last_type == TokenType::LITERAL || 
                last_type == TokenType::VARIABLE || 
                last_was_close_bracket);
    }

    return false;
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
    char c = peek_current();
    
    while (c != '\0') {
        c = advance();
        if (std::isspace(c)) continue;

        //implicit multiplication like 2x or x(1+2)
        if (needs_implicit_multiplication(c)) {
            tokens.push_back(TokenFactory::create_operator(OperatorType::MULTIPLICATION));
        }

        if (operator_list.count(c)) { //operator 
            tokens.push_back(TokenFactory::create_operator(operator_list.at(c)));
        }
        else if (c == 'x') { //variable to modify
            tokens.push_back(TokenFactory::create_operand(TokenType::VARIABLE, 0.0));
        }
        else if (c == '(' || c == ')') {
            tokens.push_back(TokenFactory::create_seperator(c));
        }
        else if (std::isdigit(c) || c == '.') {//dot to allow doubles
            handle_digit(c); //this moves the pointer to eat the number
        }
        else if (c != '\0') {
            throw std::runtime_error("Invalid Token");
        }
    }
}




