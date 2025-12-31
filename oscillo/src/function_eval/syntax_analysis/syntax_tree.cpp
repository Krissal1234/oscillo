#include "syntax_tree.h"
#include "token.h"
#include <limits>
Node::~Node() {};

//constructors
BinOpNode::BinOpNode(std::unique_ptr<Node> left, std::unique_ptr<Node> right, OperatorType op_type) : left(std::move(left)), right(std::move(right)), op_type(op_type) {};

double BinOpNode::evaluate(double x) {
    double left_val = left->evaluate(x);
    double right_val = right->evaluate(x);
    
    switch (op_type) {
            case OperatorType::ADDITION:       return left_val + right_val;
            case OperatorType::SUBTRACTION:    return left_val - right_val;
            case OperatorType::MULTIPLICATION: return left_val * right_val;
            case OperatorType::DIVISION:       
                if (right_val == 0) {
                return std::numeric_limits<double>::infinity();
                }
                return left_val / right_val;
            default: return 0;
        }
}

NumNode::NumNode(TokenType type, double value) : tok_type(type), value(value) {};


double NumNode::evaluate(double x) {
    return (tok_type == TokenType::VARIABLE) ? x : value;
}


