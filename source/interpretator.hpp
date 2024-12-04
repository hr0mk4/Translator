#ifndef INTERPRETATOR_H
#define INTERPRETATOR_H

#include "Parser.hpp"
#include "executer.hpp"
#include <string>
#include <iostream>

namespace task3 {
    class Interpretator {
        Parser pars;
        Executer E;
    public:
        Interpretator(std::string program);
        void interpretation();
    };
}

#endif