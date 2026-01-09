#include "parser.h"
#include <cmath>


// Parser functions
Parser::Parser(std::vector<std::unique_ptr<Token>> tokens) : tokens(std::move(tokens)) {};


Token* Parser::peek() {
    if (pos >= tokens.size()) return nullptr;
    return tokens[pos].get();
}

Token* Parser::advance() {
    Token* current = peek();

    if (current != nullptr) {
        pos++;
    } 

    return current;
}

std::unique_ptr<Node> Parser::parse_expression() {
    auto left = parse_term();

    while (peek() != nullptr && peek()->get_tok_type() == TokenType::OPERATOR) {
        
        OperatorType op = peek()->get_operator_type();
        
        if (op != OperatorType::ADDITION && op != OperatorType::SUBTRACTION) {
            break; 
        }

        advance(); 
        auto right = parse_term();

        left = std::make_unique<BinOpNode>(std::move(left), std::move(right), op);
    }

    return left;
}


std::unique_ptr<Node> Parser::parse_term() {

    auto left = parse_power();

    while (peek() != nullptr && peek()->get_tok_type() == TokenType::OPERATOR) {
        
        OperatorType op = peek()->get_operator_type();
        
        if (op != OperatorType::DIVISION && op != OperatorType::MULTIPLICATION) {
            break; 
        }

        advance(); 
        auto right = parse_power();

        left = std::make_unique<BinOpNode>(std::move(left), std::move(right), op);
    }

    return left;
}

//handles ^ operator
std::unique_ptr<Node> Parser::parse_power() {
    auto left = parse_factor();

    while (peek() != nullptr && peek()->get_tok_type() == TokenType::OPERATOR) {

        OperatorType op = peek()->get_operator_type();
        if (op != OperatorType::POWER) break; 
        
        advance(); //eat ^
        
        if (!peek() || peek()->get_seperator_type() != SeperatorType::OPEN_BRACKET) {
            throw std::runtime_error("Power operator '^' requires parentheses for the exponent: base^(exp)");
        }
        advance(); // eat (

        auto right = parse_expression();

        if (!peek() || peek()->get_seperator_type() != SeperatorType::CLOSE_BRACKET) {
            throw std::runtime_error("Expected ')' after exponent");
        }

        advance(); // eat )

        left = std::make_unique<BinOpNode>(std::move(left), std::move(right), OperatorType::POWER);
    }

    return left;

}

std::unique_ptr<Node> Parser::parse_factor() {
    //seperators
    Token* tk = peek();

    if (!tk) throw std::runtime_error("Unexpected end");

    TokenType tk_type = tk->get_tok_type();

    if (tk_type == TokenType::FUNCTION) {
        FunctionToken* func_tok = static_cast<FunctionToken*>(tk);
        FunctionType func_type = tk->get_func_type();
        advance(); //to eat up the function e.g. sin

        Token* next = peek(); //we expect a open bracket here
        if (!next || next->get_seperator_type() != SeperatorType::OPEN_BRACKET) {
            throw std::runtime_error("Expected ( ");
        }
        advance(); // eat (

        auto arg = parse_expression();

        Token* closing = peek();

        if (!closing || closing->get_seperator_type() != SeperatorType::CLOSE_BRACKET) {
            throw std::runtime_error("Expected )");
        }

        advance(); //eat )

        return std::make_unique<FunctionNode>(func_type, std::move(arg));
    }


    //we return a num node if it is a literal
    if (tk_type == TokenType::LITERAL || tk_type == TokenType::VARIABLE) {
        OperandToken* operand_tok = static_cast<OperandToken*>(tk);

        double val = operand_tok->value;
        advance();

        return std::make_unique<NumNode>(tk_type, val);
    }



    //if its a open bracket we have to return the expression
    if (tk->get_seperator_type() == SeperatorType::OPEN_BRACKET) {
        advance(); //this eats (

        auto node = parse_expression();

        advance(); //eats )

        return node;
    }

    throw std::runtime_error("Expected a number or parenthesis, but found something else");
}

