#pragma once
enum class TokenType {VARIABLE, LITERAL, OPERATOR, SEPERATOR, FUNCTION};
enum class FunctionType {NONE, LOG, SQRT, COS, SIN, TAN, ABS, EXP};
enum class OperatorType {NONE, DIVISION, MULTIPLICATION, ADDITION, SUBTRACTION, CARET};
enum class SeperatorType {NONE, OPEN_BRACKET, CLOSE_BRACKET};

// Base class
class Token {

    protected:
    TokenType tok_type;
    Token(TokenType tok_type);

    public:
    TokenType get_tok_type() {
        return tok_type;
    }
    virtual void print() const = 0;
    virtual ~Token() = default; //destructor runs when object goes out of scope
    
    virtual OperatorType get_operator_type() const { 
        return OperatorType::NONE; 
    }
    virtual SeperatorType get_seperator_type() const {
        return SeperatorType::NONE;
    }
    virtual FunctionType get_func_type() const {
        return FunctionType::NONE;
    }


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
    OperatorType get_operator_type() const override;

    void print() const override;
};

class SeperatorToken : public Token {
    SeperatorType sep_type;
    
    public:
    SeperatorToken(SeperatorType sep_type);
    SeperatorType get_seperator_type() const override;
    void print() const override;
};

class FunctionToken : public Token { 
    FunctionType func_type;

    public:
    FunctionToken(FunctionType func_type);
    FunctionType get_func_type() const override;
    void print() const override;

};
