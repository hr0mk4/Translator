#include "Parser.hpp"
#include <iostream>

using namespace task3;

Parser::Parser(const std::string program): scan(program) {}

Table_ident& Parser::get_TID() {
    return TID;
}

bool Parser::check_rec(std::string s) {
    for(int i = 0; i < poss_recs.size(); ++i)
        if (poss_recs[i].rec_name == s)
            return true;
    return false;
}

void Parser::gl() {
    curr_lex = scan.get_lex(id_name);
    if (curr_lex.get_type() == LEX_ID)
        curr_lex = Lex(LEX_ID, TID.put(id_name));
	c_type = curr_lex.get_type();
	c_val = curr_lex.get_value();
}

void Parser::analyze() {
    gl();
    P();
    /*prog.print();
    std::cout << std::endl << "YES!!!" << std::endl;*/
}

void Parser::P() {
    if(c_type == LEX_PROGRAM) 
        gl();
	else 
        throw curr_lex;
    while(c_type == LEX_RECORD) {
        Rec();
    }
	D1();
    if (c_type != LEX_SEMICOLON) 
        throw curr_lex;
    gl();
    B();
    if (c_type != LEX_FIN)
        throw curr_lex;
}

void Parser::Rec() {
    gl();
    if (c_type != LEX_ID)
        throw curr_lex;
    if(check_rec(id_name))
        throw "second rec";
    Recs r;
    r.rec_name = id_name;
    gl();
    if (c_type != LEX_BEGIN)
        throw curr_lex;
    do {
        gl();
        d_rec(r);
    } while (c_type == LEX_COMMA);
    poss_recs.push_back(r);
    if (c_type != LEX_END)
        throw curr_lex;
    gl();
    if (c_type != LEX_SEMICOLON)
        throw curr_lex;
    gl();
}

void Parser::d_rec(Recs& r) {
    if (c_type != LEX_ID)
        throw curr_lex;
    r.sub_rec_name = "not";
    r.fields.push_back(std::make_pair(id_name, LEX_NULL));
    gl();
    while (c_type == LEX_COMMA) {
        gl();
        if (c_type != LEX_ID)
            throw curr_lex;
        r.fields.push_back(std::make_pair(id_name, LEX_NULL));
        gl();
    }
    
    if(c_type != LEX_COLON)
        throw curr_lex;
    gl();
    if (c_type == LEX_INT || c_type == LEX_BOOL)
        for(int i = 0; i < r.fields.size(); ++i) 
            r.fields[i].second = c_type;
    else if (check_rec(id_name))
        r.sub_rec_name = id_name;
    else 
        throw curr_lex;
    gl();
}

void Parser::D1() {
    if (c_type == LEX_VAR) {
        gl();
        D();
        while (c_type == LEX_COMMA) {
            gl();
            D();
        }
    }
    else {
        throw curr_lex;
    }
}

void Parser::D() {
    st_int = std::stack<int>();
    st_r = std::stack<std::string>();   
    //st_lex = std::stack<type_of_lex>();
    if (c_type != LEX_ID)
        throw curr_lex;
    st_int.push(c_val);
    st_r.push(id_name);
    //st_lex.push(c_type);
    gl();
    while (c_type == LEX_COMMA) {
        gl();
        if (c_type != LEX_ID)
            throw curr_lex;
        st_int.push(c_val);
        st_r.push(id_name);
        //st_lex.push(c_type);
        gl();
    }
    if (c_type != LEX_COLON)
        throw curr_lex;
    gl();
    if (c_type == LEX_INT) {
        dec(LEX_INT);
        gl();
    }
    else if (c_type == LEX_BOOL) {
        dec(LEX_BOOL);
        gl();
    }
    else if (check_rec(id_name)) {
        dec_rec(id_name);
        gl();
    }
    else {
        throw curr_lex;
    }
}

void Parser::B() {
    if (c_type != LEX_BEGIN)
        throw curr_lex;
    gl();
    S();
    while (c_type == LEX_SEMICOLON) {
        gl();
        S();
    }
    if (c_type != LEX_END)
        throw curr_lex;
    gl();
}

void Parser::S() {
    int pl0, pl1, pl2, pl3;
    if (c_type == LEX_IF) {
        gl();
        E();
        eq_bool();
        pl2 = prog.get_free();
        prog.blank();
        prog.put_lex(Lex(POLIZ_FGO));
        if (c_type == LEX_THEN) {
            gl();
            S();
            if (c_type != LEX_SEMICOLON)
                throw curr_lex;
            gl();
            pl3 = prog.get_free();
            prog.blank();
            prog.put_lex(Lex(POLIZ_GO));
            prog.put_lex(Lex(POLIZ_LABEL, prog.get_free()), pl2);
            if (c_type == LEX_ELSE) {
                gl();
                S();
                prog.put_lex(Lex(POLIZ_LABEL, prog.get_free()), pl3);
            }
            else {
                throw curr_lex;
            }
        }
        else {
            throw curr_lex;
        }
    } 
    else if (c_type == LEX_WHILE) {
        pl0 = prog.get_free();
        gl();
        E();
        eq_bool();
        pl1 = prog.get_free();
        prog.blank();
        prog.put_lex(Lex(POLIZ_FGO));
        if (c_type == LEX_DO) {
            gl();
            S();
            prog.put_lex(Lex(POLIZ_LABEL, pl0));
            prog.put_lex(Lex(POLIZ_GO));
            prog.put_lex(Lex(POLIZ_LABEL, prog.get_free()), pl1);
        }
        else {
            throw curr_lex;
        }
    } 
    else if (c_type == LEX_READ) {
        gl();
        if (c_type == LEX_LPAREN) {
            gl();
            if (c_type == LEX_ID) {
                check_id_in_read();
                prog.put_lex(Lex(POLIZ_ADDRESS, c_val));
                gl();
            }
            else {
                throw curr_lex;
            }
            if (c_type == LEX_RPAREN) {
                gl();
                prog.put_lex(Lex(LEX_READ));
            }
            else {
                throw curr_lex;
            }
        }
        else {
            throw curr_lex;
        }
    }
    else if (c_type == LEX_WRITE) {
        gl();
        if (c_type == LEX_LPAREN) {
            gl();
            E();
            if (c_type == LEX_RPAREN) {
                gl();
                prog.put_lex(Lex(LEX_WRITE));
            }
            else {
                throw curr_lex;
            }
        }
        else {
            throw curr_lex;
        }
    } 
    else if (c_type == LEX_ID) {
        if (is_rec(id_name)) {
            std::string s1 = id_name;
            gl();
            if (c_type != LEX_ASSIGN) 
                throw curr_lex;
            gl();
            if (c_type != LEX_ID || !is_rec(id_name))
                throw curr_lex;
            std::string s2 = id_name;
            rec_assign(s1, s2);
            gl();
        }
        else {
            check_id();
            prog.put_lex(Lex(POLIZ_ADDRESS, c_val));
            gl();
            if (c_type != LEX_ASSIGN)
                throw curr_lex;
            gl();
            E();
            eq_type();
            prog.put_lex(Lex(LEX_ASSIGN));
        }
    } 
    else if (c_type == LEX_END) {
        return;
    }
    else 
        B();
}

bool Parser::is_rec(std::string s) {
    std::vector<Ident> buf = TID_search(s);
    for (auto a : buf)
        if (a.get_name().find('.') != std::string::npos)
            return true;
    return false;
}

void Parser::dec(type_of_lex type) {
    while (!st_int.empty()) {
        int i = st_int.top();
        st_int.pop();
        if (TID[i].get_declare())
            throw "twice";
        TID[i].put_declare();
        TID[i].put_type(type);
    }
}

void Parser::dec_rec(std::string s) {
    while(!st_r.empty()) {
        std::string main_part = st_r.top();
        st_r.pop();
        int index = TID.put(main_part);
        TID[index].put_declare();
        TID[index].put_type(LEX_RECORD);
        Recs r = get_rec(s);
        for (auto t : r.fields) {
            std::string second_part = t.first;
            std::string var = main_part + "." + second_part;
            int index = TID.put(var);
            TID[index].put_type(t.second);
            TID[index].put_declare();
        }
    }
}

Recs Parser::get_rec(std::string s) {
    for(int i = 0; i < poss_recs.size(); ++i)
        if (poss_recs[i].rec_name == s)
            return poss_recs[i];
    throw "undefined record";
}

void Parser::rec_assign(std::string s1, std::string s2)
{
    std::vector<Ident> v1 = TID_search(s1);
    std::vector<Ident> v2 = TID_search(s2);
    if (v1.size() != v2.size())
        throw "assign different reports";
    for (int i = 0; i < v1.size(); ++i) {
        if (get_postfix(v1[i].get_name()) != get_postfix(v2[i].get_name()) || v1[i].get_type() != v2[i].get_type())
            throw "assign different reports";
        int dest_id = TID.put(v1[i].get_name());
        int src_id = TID.put(v2[i].get_name());
        prog.put_lex(Lex(POLIZ_ADDRESS, dest_id));
        prog.put_lex(Lex(LEX_ID, src_id));
        prog.put_lex(Lex(LEX_ASSIGN));
    }
}

std::vector<Ident> Parser::TID_search(std::string prefix)
{
    std::vector<Ident> result;
    for (int i = 0; i < TID.size(); ++i)
        if (get_prefix(TID[i].get_name()) == prefix && TID[i].get_name() != prefix)
            result.push_back(TID[i]);
    return result;
}

std::string Parser::get_prefix(std::string str)
{
    std::string result;
    for (auto c : str) {
        if (c == '.')
            break;
        result += c;
    }
    return result;
}

std::string Parser::get_postfix(std::string str)
{
    std::string result;
    int i;
    for (i = 0; i < str.length(); ++i)
        if (str[i] == '.') {
            ++i;
            break;
        }
    for (; i < str.length(); ++i)
        result += str[i];
    return result;
}

void Parser::check_id() {
    if (TID[c_val].get_declare())
        st_lex.push(TID[c_val].get_type());
    else
        throw "not_declared";
}

void Parser::check_op() {
    type_of_lex t1, t2, op;
    t2 = st_lex.top();
    st_lex.pop();
    op = st_lex.top();
    st_lex.pop();
    if (op == LEX_UNARY_MINUS) {
        if (t2 == LEX_INT || t2 == LEX_ID) 
            st_lex.push(t2);
        else 
            throw "wrong_types_in_operation";
    } else {
        t1 = st_lex.top();
        st_lex.pop();
        type_of_lex t = (op == LEX_OR || op == LEX_AND) ? LEX_BOOL : LEX_INT;
        if (t1 == t2 && t1 == t)
            st_lex.push(t);
        else
            throw "wrong types in operation";
    }
}

void Parser::check_not()
{
    type_of_lex t = st_lex.top();
    st_lex.pop();
    if (t != LEX_BOOL)
        throw "wrong type in not";
    else
        st_lex.push(LEX_BOOL);
}

void Parser::eq_type()
{
    type_of_lex t1, t2;
    t1 = st_lex.top();
    st_lex.pop();
    t2 = st_lex.top();
    st_lex.pop();
    if (t1 != t2)
        throw "wrong_type_in_:=";
}

void Parser::eq_bool()
{
    type_of_lex t = st_lex.top();
    st_lex.pop();
    if(t != LEX_BOOL)
        throw "expression_is_not_bool";
}

void Parser::check_id_in_read()
{
    if (!TID[c_val].get_declare())
        throw "not_declared";
}

void Parser::E() {
    E1();
    if (c_type == LEX_EQUAL || c_type == LEX_LESS ||
        c_type == LEX_GREATER || c_type == LEX_LEQ ||
        c_type == LEX_GEQ || c_type == LEX_NEQ) 
    {
        st_lex.push(c_type);
        type_of_lex relation = c_type;
        gl();
        E1();
        check_op();
        st_lex.pop();
        st_lex.push(LEX_BOOL);
        prog.put_lex(relation);
    }
}

void Parser::E1() {
    T();
    while (c_type == LEX_PLUS || 
           c_type == LEX_MINUS || c_type == LEX_OR) {
        type_of_lex operation = c_type;
        st_lex.push(c_type);
        gl();
        T();
        check_op();
        prog.put_lex(Lex(operation));
    }
}

void Parser::T() {
    F();
    while (c_type == LEX_TIMES || c_type == LEX_SLASH || c_type == LEX_AND) {
        type_of_lex operation = c_type;
        st_lex.push(c_type);
        gl();
        F();
        check_op();
        prog.put_lex(Lex(operation));
    }
}

void Parser::F()
{
    switch(c_type) {
        case(LEX_ID):
            check_id();
            prog.put_lex(Lex(LEX_ID, c_val));
            gl();
            break;
        case(LEX_NUM):
            st_lex.push(LEX_INT);
            prog.put_lex(curr_lex);
            gl();
            break;
        case(LEX_TRUE):
            st_lex.push(LEX_BOOL);
            prog.put_lex(Lex(LEX_TRUE, 1));
            gl();
            break;
        case(LEX_FALSE):
            st_lex.push(LEX_BOOL);
            prog.put_lex(Lex(LEX_FALSE, 0));
            gl();
            break;
        case(LEX_NOT):
            gl();
            F();
            check_not();
        case(LEX_LPAREN):
            gl();
            E();
            if (c_type == LEX_RPAREN)
                gl();
            else    
                throw curr_lex;
            break;
        case(LEX_MINUS):
            st_lex.push(LEX_UNARY_MINUS);
            gl();
            F();
            check_op();
            prog.put_lex(Lex(LEX_UNARY_MINUS));
            break;
        default:
            throw curr_lex;
    }
}