#include "interpretator.hpp"
#include "Parser.hpp"

using namespace task3;

Interpretator::Interpretator(std::string program): pars(program) {}

void Interpretator::interpretation() {
    pars.analyze();
    
    E.execute(pars.prog, pars.get_TID());
}