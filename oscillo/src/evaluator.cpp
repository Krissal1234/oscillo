#include "evaluator.h"
#include "lexer.h"
#include "parser.h"


//constructor returns root, so that we dont need to build the tree every time we evaluate
Evaluator::Evaluator(std::string_view input, Plotter& plotter) : input_str(input), plotter(plotter){
    Lexer l(input_str);
    l.tokenise();
    Parser p(l.get_tokens());

    this->root = p.parse_expression();
}


double Evaluator::evaluate(double x) {
    if (!root) throw std::runtime_error("root is null");

    return root->evaluate(x);
}

void Evaluator::plot_function() {

    double x_max = plotter.get_xmax();
    double x_min = plotter.get_xmin();
    double p_cols = plotter.get_pcols();

    double math_width = x_max - x_min;
    double step = math_width / p_cols; 

    for (int i = 1; i < p_cols; ++i) {
        double math_x = x_min + (i * step);
        double math_y = evaluate(math_x); 
        plotter.plot(math_x, math_y);
    }

    plotter.render();
}
void Evaluator::plot_axes() {
    plotter.plot_and_render_axes();
}


