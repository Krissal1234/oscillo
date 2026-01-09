#include <iostream>
#include <vector>
#include <string>
#include "evaluator.h"
#include "plotter.h"

struct Test {
std::string expr;
double x;
double expected;
};

void run_evaluator_tests() {
std::vector<Test> tests = {
        //arithmetic and precidence
        {"1+2+3", 0, 6.0},
        {"10-5-2", 0, 3.0},
        {"24/4/2", 0, 3.0},
        {"2+3*4", 0, 14.0},
        {"10*2-5", 0, 15.0},
        {"10/2+3", 0, 8.0},
        {"5+4/2*3", 0, 11.0},
        {"100-20*3+10", 0, 50.0},
        {"10+20/5-2", 0, 12.0},
        {"10-5+2", 0, 7},

        //brackets
        {"(2+3)*4", 0, 20.0},
        {"10/(2+3)", 0, 2.0},
        {"(10-5)-2", 0, 3.0},
        {"10-(5-2)", 0, 7.0},
        {"(2+(3*4))", 0, 14.0},
        {"((10))", 0, 10.0},
        {"2*(3+(4*5))", 0, 46.0},
        {"5+(10-(2+3))", 0, 10.0},

        // variable x substitution
        {"x", 7.5, 7.5},
        {"x+x+x", 2.0, 6.0},
        {"2*x+5", 10.0, 25.0},
        {"x*x", 4.0, 16.0},
        {"x*x-x-2", 2.0, 0.0},
        {"(x+1)*(x-1)", 4.0, 15.0},
        {"x/2", 1.0, 0.5},
        {"(x+5)/x", 2.5, 3.0},

        // Decimals
        {"0.5+0.5", 0, 1.0},
        {"2.5*4", 0, 10.0},
        {"1.25+3.75", 0, 5.0},
        {"x*1.1", 10.0, 11.0},
        {"10/4", 0, 2.5},
        {"0.1+0.2", 0, 0.3},

        // chaining
        {"1+2*3+4*5", 0, 27.0},
        {"(1+2)*(3+4)", 0, 21.0},
        {"x*x*x*x", 2.0, 16.0},
        {"(x+1)/(x+1)", 5.0, 1.0},
        {"1+(2+(3+(4+5)))", 0, 15.0},
        {"x*2+x*3+x*4", 1.0, 9.0},
        //implicit multiplication
        {"2x", 5.0, 10.0},              
        {"10x", 2.5, 25.0},            
        {"0.5x", 10.0, 5.0},          
        {"x(x+1)", 3.0, 12.0},       
        {"2(x+5)", 2.0, 14.0},      
        {"(x+1)(x-1)", 4.0, 15.0}, 
        {"2x + 3x", 2.0, 10.0},   
        {"10 - 2x", 3.0, 4.0},   
        {"2(3)(4)", 0, 24.0},   
        {"x(2x+1)", 2.0, 10.0},
};

for (const Test& t : tests) {
    try {
        
        Plotter dummyplotter(10,10);
        Evaluator eval(t.expr, dummyplotter);
        double res = eval.evaluate(t.x);
        if (std::abs(res - t.expected) < 1e-6) {
            std::cout << "PASS: " << t.expr << " (x=" << t.x << ") = " << res << "\n";
        } else {
            std::cout << "FAIL: " << t.expr << " | Got " << res << " Exp " << t.expected << "\n";
        }
    } catch (const std::exception& e) {
        std::cout << "ERR:  " << t.expr << " -> " << e.what() << "\n";
    }
}
}
