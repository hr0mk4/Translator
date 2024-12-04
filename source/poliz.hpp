#ifndef POLIZ_H
#define POLIZ_H
#include <vector>
#include "lex_analyzer.hpp"

namespace task3 {
    class Poliz {
        std::vector<Lex> v;
    public:
        void put_lex(Lex l);
        void put_lex(Lex l, int place);
        void blank();
        int get_free();
        Lex& operator[] (int index);
        void print();
    };
}


#endif