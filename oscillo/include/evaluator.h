#pragma once

#include <string>

using Function = std::string;

class Evaluator {

    protected:
    Function input_str;


    public:
    Evaluator(Function func_input);

    Function get_function();

    void set_function(Function input);

    double solve(int x);


};
    



