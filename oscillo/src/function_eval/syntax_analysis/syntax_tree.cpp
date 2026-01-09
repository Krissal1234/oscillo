#include "syntax_tree.h"
#include "token.h"
#include <limits>
#include <cmath>
Node::~Node() {};

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
            case OperatorType::POWER:           return std::pow(left_val, right_val);
            default: return 0;
        }
}

NumNode::NumNode(TokenType type, double value) : tok_type(type), value(value) {};


double NumNode::evaluate(double x) {
    return (tok_type == TokenType::VARIABLE) ? x : value;
}

FunctionNode::FunctionNode(FunctionType func_type, std::unique_ptr<Node> arg) : func_type(func_type), arg(std::move(arg)) {};

double FunctionNode::evaluate(double x) {
    double inner_value = arg->evaluate(x);

    switch (func_type) {
        case FunctionType::SIN:   return std::sin(inner_value);
        case FunctionType::COS:   return std::cos(inner_value);
        case FunctionType::TAN:   return std::tan(inner_value);
        case FunctionType::SQRT:  return std::sqrt(inner_value);
        case FunctionType::LOG:   return std::log(inner_value);
        case FunctionType::ABS:   return std::abs(inner_value);
        case FunctionType::EXP:   return std::exp(inner_value);
        default:
            return 0.0; 
    }
}

