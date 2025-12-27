#pragma once
#include <memory>
#include <vector>
#include "token.h"

class Node {
public:
    virtual ~Node() = default;
    virtual double evaluate(double x) = 0;
};

class NumNode : public Node {
    std::unique_ptr<OperandToken> token;
    double value {};
public:
    double evaluate();
    NumNode(std::unique_ptr<OperandToken> token);
};

class BinOpNode : public Node {
    std::unique_ptr<OperatorToken> op_token;
    std::unique_ptr<Node> left;
    std::unique_ptr<Node> right;
public:
    double evaluate();
    BinOpNode( std::unique_ptr<Node> left, std::unique_ptr<Node> right, std::unique_ptr<OperatorToken> op_token);
};

class Parser {
    std::vector<std::unique_ptr<Token>> tokens;
    int pos = 0;

    Token* peek(); //we return a pointer and not a ref since we can check for a nullptr to denote end of tokens

    Token* advance();

    std::unique_ptr<Node> parse_expression(); //returns root 
    std::unique_ptr<NumNode> parse_factor(); // returns leaf or subtree
    std::unique_ptr<BinOpNode> parse_term(); //returns multiplication/division tree
public:
    Parser(std::vector<std::unique_ptr<Token>> tokens);

};



