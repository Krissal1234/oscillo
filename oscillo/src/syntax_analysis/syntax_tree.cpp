#include "syntax_tree.h"


//constructors
BinOpNode::BinOpNode(std::unique_ptr<Node> left, std::unique_ptr<Node> right, std::unique_ptr<OperatorToken> op_token) : left(std::move(left)), right(std::move(right)), op_token(std::move(op_token)) {};

NumNode::NumNode(std::unique_ptr<OperandToken> token) : value(token->value), token(std::move(token)) {}

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

