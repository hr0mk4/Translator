#include "interpretator.hpp"
#include <iostream>
#include <cstdio>

int main(int argc, char *argv[]) {
    try {
        std::string program = argv[1];
        task3::Interpretator interp(program);
        interp.interpretation();
    }
    catch (char c) {
        std::cout << "unexpected symbol" << c << std::endl;
        return 1;
    }
    catch (task3::Lex l) {
        std::cout << "unexpected lexeme" << l << std::endl;
        return 1;
    }
    catch (const char* s) {
        std::cout << s << std::endl;
        return 1;
    }

    return 0;
}