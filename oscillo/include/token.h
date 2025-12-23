#pragma once


enum class TokenType {VARIABLE, LITERAL, OPERATOR, SEPERATOR};

enum class OperatorType {NONE, DIVISION, MULTIPLICATION, ADDITION, SUBTRACTION, CARET};

// Base class
class Token {

    protected:
    TokenType tok_type;
    Token(TokenType tok_type);

    public:
    virtual ~Token() = default;
};

// Seperate Token Children 
class OperandToken : public Token{

    double value {};

    public:
    OperandToken(TokenType tok_type, double value);
};


class OperatorToken : public Token{
    OperatorType op_type;

    public:
    OperatorToken(OperatorType op_type);
};

// class SeperatorToken : Token {
//
//
// };
// class FunctionToken : Token{ 
//
// };
