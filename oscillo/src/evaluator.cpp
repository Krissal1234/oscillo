#include "evaluator.h"
#include "lexer.h"
#include "parser.h"

Evaluator::Evaluator(std::string_view input) : input_str(input) {
    Lexer l(input_str);
    l.tokenise();

    Parser p(l.get_tokens());

    this->root = p.parse_expression();
};


double Evaluator::evaluate(double x) {
    if (!root) throw std::runtime_error("root is null");

    return root->evaluate(x);
}
