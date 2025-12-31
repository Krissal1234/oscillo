#pragma once
#include "syntax_tree.h"
#include <memory>
#include <plotter.h>


class Evaluator {

    std::string_view input_str;
    std::unique_ptr<Node> root;
    Plotter& plotter;

    public:
    Evaluator(std::string_view input, Plotter& plotter);

    void plot_function(); 
    void plot_axes();
    double evaluate(double x);
};
    



