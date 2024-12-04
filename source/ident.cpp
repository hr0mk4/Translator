#include "ident.hpp"

task3::Ident::Ident(): declare(false), assign(false), name(std::string()), value(NULL) {} //There may be a prob

std::string task3::Ident::get_name() const { return name; }

void task3::Ident::put_name(const std::string s) { name = s; }

bool task3::Ident::get_declare() const { return declare; }

void task3::Ident::put_declare() { declare = true; }

task3::type_of_lex task3::Ident::get_type() const { return type; }

void task3::Ident::put_type(task3::type_of_lex t) { type = t; }

bool task3::Ident::get_assign() const { return assign; }

void task3::Ident::put_assign() { assign = true; }

int task3::Ident::get_value() const { return value; }

void task3::Ident::put_value(int v) { //may be mistaken
    if (type == LEX_BOOL)
        value = v != 0;
    else if (type == LEX_INT)
        value = v;
    else 
        throw "bad_type";
    value = v;
 }

 task3::Ident& task3::Table_ident::operator[](int k) { //there may be mistake
    if (k < v.size())
        return v[k];
    else 
        throw "Table_Ident:Out of range";
 }

 int task3::Table_ident::put(const std::string s) {
    for (int i = 0; i < v.size(); ++i)
        if (v[i].get_name() == s)
            return i;
    Ident id;
    id.put_name(s);
    v.push_back(id);
    return v.size() - 1;
 }

int task3::Table_ident::size() { return v.size(); }