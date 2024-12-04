#include "lex_analyzer.hpp"

task3::Lex::Lex(const task3::type_of_lex t, const int v): t_lex(t), v_lex(v) {}

task3::type_of_lex task3::Lex::get_type() const { return t_lex; }

int task3::Lex::get_value() const { return v_lex; }

std::ostream& task3::operator<<(std::ostream& s, task3::Lex l) {
    s << '(' << l.t_lex << ',' << l.v_lex << ");";
    return s;
}