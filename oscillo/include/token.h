#pragma once


enum class TokenType {VARIABLE, LITERAL, OPERATOR, SEPERATOR};

enum class OperatorType {NONE, DIVISION, MULTIPLICATION, ADDITION, SUBTRACTION, CARET};

// Base class
class Token {

    protected:
    TokenType tok_type;
    Token(TokenType tok_type);

    public:
    virtual void print() const = 0;
    virtual ~Token() = default; //destructor runs when object goes out of scope
};

// Seperate Token Children 
class OperandToken : public Token{

    double value {};

    public:
    void print() const override;
    OperandToken(TokenType tok_type, double value);
};


class OperatorToken : public Token{
    OperatorType op_type;

    public:
     void print() const override;
    OperatorToken(OperatorType op_type);
};

// class SeperatorToken : Token {
//
//
// };
// class FunctionToken : Token{ 
//
// };
