#include "executer.hpp"

using namespace task3;

void Executer::execute(Poliz& prog, Table_ident& TID) {
    std::stack<int> args;
    int i, j, index = 0, size = prog.get_free();
    while (index < size) {
        pc_el = prog[index];
        switch(pc_el.get_type()) {
            case LEX_TRUE:
            case LEX_FALSE:
            case LEX_NUM:
            case POLIZ_ADDRESS:
            case POLIZ_LABEL: {
                args.push(pc_el.get_value());
                break;
            }
            case LEX_ID: {
                i = pc_el.get_value();
                if (TID[i].get_assign())
                    args.push(TID[i].get_value());
                else
                    throw "Poliz:bad indefinite";
                break;
            }
            case LEX_NOT: {
                int top = args.top();
                args.pop();
                args.push(!top);
                break;
            }
            case LEX_OR: {
                i = args.top();
                args.pop();
                int top = args.top();
                args.pop();
                args.push(top || i);
                break; 
            }
            case LEX_AND: {
                i = args.top();
                args.pop();
                int top = args.top();
                args.pop();
                args.push(top && i);
                break;
            }
            case POLIZ_GO: {
                index = args.top() - 1;
                args.pop();
                break;
            }
            case POLIZ_FGO: {
                i = args.top();
                args.pop();
                int top = args.top();
                args.pop();
                if (!top) 
                    index = i - 1;
                break;
            }
            case LEX_WRITE: {
                int top = args.top();
                args.pop();
                std::cout << top << std::endl;
                break;
            }
            case LEX_READ: {
                int k;
                i = args.top();
                args.pop();
                if (TID[i].get_type() == LEX_INT) {
                    std::cin >> k;
                }
                else {
                    std::string input;
                    while(true) {
                        std::cin >> input;
                        if (input == "true") {
                            k = 1;
                            break;
                        }
                        else if (input == "false") {
                            k = 0;
                            break;
                        }
                        else {
                            std::cout << "Error input: true/false, try again" << std::endl;
                        }
                    }
                }
                TID[i].put_value(k);
                TID[i].put_assign();
                break;
            }
            case LEX_PLUS: {
                int t1, t2;
                t1 = args.top();
                args.pop();
                t2 = args.top();
                args.pop();
                args.push(t1 + t2);
                break;
            }
            case LEX_TIMES: {
                int t1, t2;
                t1 = args.top();
                args.pop();
                t2 = args.top();
                args.pop();
                args.push(t1 * t2);
                break;
            }
            case LEX_MINUS: {
                int t1, t2;
                t1 = args.top();
                args.pop();
                t2 = args.top();
                args.pop();
                args.push(t2 - t1);
                break;
            }
            case LEX_UNARY_MINUS: {
                int t1;
                t1 = args.top();
                args.pop();
                args.push(-t1);
                break;
            }
            case LEX_SLASH: {
                i = args.top();
                args.pop();
                if (i) {
                    j = args.top();
                    args.pop();
                    args.push(j / i);
                    break;
                }
                else {
                    throw "Poliz:divide by zero";
                }
            }
            case LEX_EQUAL: {
                int t1, t2;
                t1 = args.top();
                args.pop();
                t2 = args.top();
                args.pop();
                args.push(t1 == t2);
                break;
            }
            case LEX_LESS: {
                int t1, t2;
                t1 = args.top();
                args.pop();
                t2 = args.top();
                args.pop();
                args.push(t1 > t2);
                break;
            }
            case LEX_GREATER: {
                int t1, t2;
                t1 = args.top();
                args.pop();
                t2 = args.top();
                args.pop();
                args.push(t1 < t2);
                break;
            }
            case LEX_LEQ: {
                int t1, t2;
                t1 = args.top();
                args.pop();
                t2 = args.top();
                args.pop();
                args.push(t1 >= t2);
                break;
            }
            case LEX_GEQ: {
                int t1, t2;
                t1 = args.top();
                args.pop();
                t2 = args.top();
                args.pop();
                args.push(t1 <= t2);
                break;
            }
            case LEX_NEQ: {
                int t1, t2;
                t1 = args.top();
                args.pop();
                t2 = args.top();
                args.pop();
                args.push(t1 != t2);
                break;
            }
            case LEX_ASSIGN: {
                i = args.top();
                args.pop();
                j = args.top();
                args.pop();
                TID[j].put_value(i);
                TID[j].put_assign();
                break;
            }
            default:
                throw "Poliz:unexpected element";
        }
        ++index;
    }
}