#pragma once
#include "syntax_tree.h"
#include <memory>


class Evaluator {

    std::string_view input_str;
    std::unique_ptr<Node> root;

    public:
    Evaluator(std::string_view input);

    double evaluate(double x);


};
    



