#ifndef LEX_ANALYZER_H
#define LEX_ANALYZER_H
#include <iostream>

namespace task3 {
    enum type_of_lex {
        LEX_NULL,
        LEX_PROGRAM,
        LEX_BEGIN,
        LEX_END,
        LEX_VAR,
        LEX_RECORD,
        LEX_ASSIGN,
        LEX_INT,
        LEX_BOOL,
        LEX_WRITE,
        LEX_READ,
        LEX_FIN,
        LEX_COLON, 
        LEX_LPAREN,
        LEX_RPAREN,
        LEX_EQUAL,
        LEX_NEQ,
        LEX_LEQ,
        LEX_LESS,
        LEX_GEQ,
        LEX_GREATER,
        LEX_PLUS,
        LEX_MINUS,
        LEX_UNARY_MINUS,
        LEX_TIMES,
        LEX_SLASH,
        LEX_SEMICOLON, 
        LEX_COMMA, 
        LEX_NUM,
        LEX_ID,
        LEX_WHILE,
        LEX_DO,
        LEX_IF,
        LEX_THEN,
        LEX_ELSE,
        LEX_AND, 
        LEX_OR,
        LEX_NOT,
        LEX_TRUE,
        LEX_FALSE,
        POLIZ_LABEL,
        POLIZ_ADDRESS,
        POLIZ_GO,
        POLIZ_FGO
    };

    class Lex  {
        type_of_lex t_lex;
        int v_lex;
    public:
        Lex(const type_of_lex t = LEX_NULL, const int v = 0);
        type_of_lex get_type() const;
        int get_value() const;
        friend std::ostream& operator<<(std::ostream& s, Lex l);
    };
}
#endif