#pragma once
#include <memory>
#include <vector>
#include "token.h"

class Node {
public:
    virtual ~Node();
    virtual double evaluate(double x) = 0;
};

class NumNode : public Node {
    TokenType tok_type; //it could be variable or literal
    double value {};
public:
    double evaluate(double x) override;
    NumNode(TokenType type, double value);
};

// change this so that it only uses OperatorType, why do we need to give it operator Token
class BinOpNode : public Node {
    OperatorType op_type;
    std::unique_ptr<Node> left;
    std::unique_ptr<Node> right;
public:
    double evaluate(double x) override;
    BinOpNode( std::unique_ptr<Node> left, std::unique_ptr<Node> right, OperatorType op_type);
};



