#ifndef PARSER_H
#define PARSER_H

#include "lex_analyzer.hpp"
#include "scanner.hpp"
#include "poliz.hpp"
#include <stack>
#include <map>

namespace task3 {
    struct Recs {
        std::string rec_name;
        std::vector<std::pair<std::string, type_of_lex>> fields;
        std::string sub_rec_name;
    };
    class Parser {
        Table_ident TID;
        Lex curr_lex;
        type_of_lex c_type;
        int c_val;
        Scanner scan;
        std::stack<int> st_int;
        std::stack<type_of_lex> st_lex;
        std::vector<Recs> poss_recs;
        std::string id_name;
        std::stack<std::string> st_r;
        //std::map<std::string, 
        void P();
        void Rec();
        void d_rec(Recs& r);
        void D1();
        void D();
        void B();
        void S();
        void E();
        void E1();
        void T();
        void F();

        bool check_rec(std::string s);
        void dec(type_of_lex type);
        void dec_rec(std::string s);
        void check_id();
        void check_op();
        void check_not();
        Recs get_rec(std::string s);
        bool is_rec(std::string s);
        void eq_type();
        void rec_assign(std::string s1, std::string s2);
        std::string get_postfix(std::string s);
        std::string get_prefix(std::string s);
        std::vector<Ident> TID_search(std::string s);
        void eq_bool();
        void check_id_in_read();
        void gl(); // получить очередную лексему
    public:
        Poliz prog;
        Parser(const std::string program);
        void analyze();
        Table_ident& get_TID();
    };
}


#endif