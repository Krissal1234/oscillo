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
        
        expect_seperator(SeperatorType::OPEN_BRACKET);
        advance(); // eat (

        auto right = parse_expression();

        expect_seperator(SeperatorType::CLOSE_BRACKET);

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

    if (is_unary_op(tk)) {
        return parse_unary(); //handles negative numbers
    }


    if (tk->get_tok_type() == TokenType::FUNCTION) {
        return parse_factor_function_call();
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
        return parse_parentheses();
    }

    throw std::runtime_error("Expected a number or parenthesis, but found something else");
}

//helper functions

bool Parser::is_unary_op(Token* tk) {
    return tk->get_tok_type() == TokenType::OPERATOR && 
          (tk->get_operator_type() == OperatorType::SUBTRACTION || 
           tk->get_operator_type() == OperatorType::ADDITION);
}

std::unique_ptr<Node> Parser::parse_unary() {
    Token* op_tk = advance(); // eat -
    auto operand = parse_factor(); 

    // We make a new binary op node that subtracts 0 from operand, making it a negative numeber
    if (op_tk->get_operator_type() == OperatorType::SUBTRACTION) {
        auto zero = std::make_unique<NumNode>(TokenType::LITERAL, 0.0);

        return std::make_unique<BinOpNode>(
            std::move(zero), 
            std::move(operand), 
            OperatorType::SUBTRACTION
        );
    }
    return operand;
}

std::unique_ptr<Node> Parser::parse_parentheses() {
    advance(); // eat (
    auto node = parse_expression();
    
    expect_seperator(SeperatorType::CLOSE_BRACKET);
    advance(); // eat )
    
    
    return node;
}

std::unique_ptr<Node> Parser::parse_factor_function_call() {

    FunctionType func_type = advance()->get_func_type();

    expect_seperator(SeperatorType::OPEN_BRACKET);
    advance(); // eat (

    auto arg = parse_expression();

    expect_seperator(SeperatorType::CLOSE_BRACKET);
    advance(); //eat )

    return std::make_unique<FunctionNode>(func_type, std::move(arg));
}

void Parser::expect_seperator(SeperatorType type) {
    if (!peek()|| peek()->get_seperator_type() != type) {
        throw std::runtime_error("Syntax error");
    }
}
