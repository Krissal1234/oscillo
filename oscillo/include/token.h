#pragma once


enum class TokenType {VARIABLE, LITERAL, OPERATOR, SEPERATOR};

enum class OperatorType {NONE, DIVISION, MULTIPLICATION, ADDITION, SUBTRACTION, CARET};
enum class SeperatorType {OPEN_BRACKET, CLOSE_BRACKET};

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
    public:
    OperandToken(TokenType tok_type, double value);
    double value {};
    void print() const override;
};


class OperatorToken : public Token{
    OperatorType op_type;

    public:
    OperatorToken(OperatorType op_type);
     void print() const override;
};

class SeperatorToken : public Token {
    SeperatorType sep_type;
    
    public:
    SeperatorToken(SeperatorType sep_type);
    void print() const override;
};

// class FunctionToken : Token{ 
//
// };
//
