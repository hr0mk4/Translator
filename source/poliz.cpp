#include "poliz.hpp"
#include <iostream>
using namespace task3;

void Poliz::put_lex(Lex l) { v.push_back(l); }

void Poliz::put_lex(Lex l, int place) { 
    if (place >= v.size()) 
        throw "Out of range in Poliz";
    v[place] = l;
}

void Poliz::blank() { v.push_back(Lex()); }

int Poliz::get_free() { return v.size(); }

Lex& Poliz::operator[](int index) {
    if (index >= v.size())
        throw "Poliz:out of array";
    return v[index];
}

void Poliz::print() {
    for(int i = 0; i < v.size(); ++i) //might be mistaken
        std::cout << v[i];
}