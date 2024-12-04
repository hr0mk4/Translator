#include "scanner.hpp"

using namespace task3;

void Scanner::clear() { buf.clear(); }

void Scanner::add() { buf.push_back(c); }

int Scanner::look(std::string s, std::vector<std::string> list) {
    for (int i = 0; i < list.size(); ++i)
        if (s == list[i])
            return i;
    return 0;
}

void Scanner::gc() {
    f.read(&c, 1);
    if (f.eof())
        c = '@';
}

Scanner::Scanner(const std::string &program) {
    f.open(program);
    CS = H;
    clear();
    gc();
}

std::vector<std::string> Scanner::TW = 
{
    "",
    "and",
    "begin",
    "end",
    "bool",
    "do",
    "else",
    "if",
    "false",
    "int",
    "not",
    "or",
    "program",
    "read",
    "then",
    "true",
    "var",
    "while",
    "write",
    "record"
};

std::vector<std::string> Scanner::TD =
{
    "",
    "@",
    ";",
    ",",
    ":",
    ":=",
    "(",
    ")",
    "=",
    "<",
    ">",
    "+",
    "-",
    "*",
    "/",
    "<=",
    "!=",
    ">="
};

std::vector<type_of_lex> Scanner::words =
{
    LEX_NULL,
    LEX_AND,
    LEX_BEGIN,
    LEX_END,
    LEX_BOOL,
    LEX_DO,
    LEX_ELSE,
    LEX_IF,
    LEX_FALSE,
    LEX_INT,
    LEX_NOT,
    LEX_OR,
    LEX_PROGRAM,
    LEX_READ,
    LEX_THEN,
    LEX_TRUE,
    LEX_VAR,
    LEX_WHILE,
    LEX_WRITE,
    LEX_RECORD
};

std::vector<type_of_lex> Scanner::dlms =
{
    LEX_NULL,
    LEX_FIN,
    LEX_SEMICOLON,
    LEX_COMMA,
    LEX_COLON,
    LEX_ASSIGN,
    LEX_LPAREN,
    LEX_RPAREN,
    LEX_EQUAL,
    LEX_LESS,
    LEX_GREATER,
    LEX_PLUS,
    LEX_MINUS,
    LEX_TIMES,
    LEX_SLASH,
    LEX_LEQ,
    LEX_NEQ,
    LEX_GEQ
};

Lex Scanner::get_lex(std::string& id_name) {
    int d, j;
    CS = H;
    do {
        switch(CS) {
            case H:
                if (c == ' ' || c == '\n' || c== '\r' || c == '\t')
                    gc();
                else if (isalpha(c)) {
                    clear();
                    add();
                    gc();
                    CS = IDENT;
                }
                else if (isdigit(c)) {
                    d = c - '0';
                    gc();
                    CS = NUMB;
                }
                else if (c == '{') {
                    gc();
                    CS = COM;
                }
                else if ( c== ':' || c== '<' || c== '>') {
                    clear();
                    add();
                    gc();
                    CS = ALE;
                }
                else if (c == '@') {
                    return Lex(LEX_FIN);
                }
                else if (c == '!') {
                    clear();
                    add();
                    gc();
                    CS = NEQ;
                }
                else {
                    CS = DELIM;
                }
                break;
            case IDENT:
                if (isalpha(c) || isdigit(c) || c == '.') {
                    add();
                    gc();
                }
                else {
                    //may be mistaken
                    id_name = buf;
                    if (j = look(buf, TW)) {
                        return Lex(words[j], j);
                    }
                    else {
                        //j = TID.put(buf);
                        return Lex(LEX_ID, 0);
                    }
                }
                break;
            case NUMB:
                if (isdigit(c)) {
                    d = d * 10 + (c - '0');
                    gc();
                }
                else {
                    return Lex(LEX_NUM, d);
                }
                break;
            case COM:
                if (c == '}') {
                    gc();
                    CS = H;
                }
                else if (c == '@' || c == '{') {
                    throw c;
                }
                else {
                    gc();
                }
                break;
            case ALE:
                if (c == '=') {
                    add();
                    gc();
                    j = look(buf, TD);
                    return Lex(dlms[j], j);
                }
                else {
                    j = look(buf, TD);
                    return Lex(dlms[j], j);
                }
                break;
            case NEQ:
                if ( c == '=' ) {
                    add();
                    gc();
                    j = look(buf, TD);
                    return Lex(LEX_NEQ, j);
                }
                else {
                    throw '!';
                }
                break;
            case DELIM:
                clear();
                add();
                if (j = look(buf, TD)) {
                    gc();
                    return Lex(dlms[j], j);
                }
                else {
                    throw c;
                }
                break;
        }
    } while (true);
}