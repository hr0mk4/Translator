#ifndef EXETURER_H
#define EXECUTER_H

#include "lex_analyzer.hpp"
#include "poliz.hpp"
#include "scanner.hpp"
#include <stack>

namespace task3 {
    class Executer {
        Lex pc_el;
    public:
        void execute(Poliz &prog, Table_ident& TID);
    };
}

#endif