#include "token.h"


Token::Token(TokenType tok_type) : tok_type(tok_type) {};

OperatorToken::OperatorToken(OperatorType op_type) : Token(TokenType::OPERATOR), op_type(op_type) {};

OperandToken::OperandToken(TokenType tok_type, double value) : Token(tok_type), value(value) {};





