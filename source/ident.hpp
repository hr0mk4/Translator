#ifndef IDENT_H
#define IDENT_H
#include <string>
#include <vector>
#include "lex_analyzer.hpp"

namespace task3 {
    class Ident {
        std::string name;
        bool declare;
        type_of_lex type;
        bool assign;
        int value;
    public:
        Ident();
        std::string get_name() const;
        void put_name(std::string s);
        bool get_declare() const;
        void put_declare();
        type_of_lex get_type() const;
        void put_type(type_of_lex t);
        bool get_assign() const;
        void put_assign();
        int get_value() const;
        void put_value(int v);
    };

    class Table_ident {
        std::vector<Ident> v;
    public:
        Ident& operator[](int k);
        int put(const std::string s);
        int size();
    };
}

#endif