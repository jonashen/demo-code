#ifndef IF_STATEMENT_INCLUDED
#define IF_STATEMENT_INCLUDED

#include "Statement.h"
#include "ProgramState.h"

class IfStatement: public Statement
{
public:
    IfStatement(std::string var, std::string op, int val, int line);
    IfStatement(std::string var, std::string op, std::string o_var, int line);
    ~IfStatement();
    
    virtual void execute(ProgramState * state, std::ostream &outf);
    
private:
    std::string var_name; // variable name
    std::string ovar_name; // other variable name (if specified)
    std::string op_name; // which operator specified
    int value; // value of the variable
    int line_num; // which line number to jump to if true
    int op_val; // value of the operator
    bool is_true; // If the comparison is true
};

#endif