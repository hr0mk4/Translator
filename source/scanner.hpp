#ifndef SCANNER_H
#define SCANNER_H
#include <vector>
#include <string>
#include <fstream>
#include "lex_analyzer.hpp"
#include "ident.hpp"

namespace task3 {
    class Scanner {
        enum state { H, IDENT, NUMB, COM, ALE, DELIM, NEQ };
        static std::vector<std::string> TW;
        static std::vector<type_of_lex> words;
        static std::vector<std::string> TD;
        static std::vector<type_of_lex> dlms;
        state CS;
        std::fstream f;
        char c;
        std::string buf;
        void clear();
        void add();
        int look(std::string s, std::vector<std::string> list);
        void gc();
    public:
        Scanner(const std::string &program);
        Lex get_lex(std::string &id_name);
    };
}


#endif