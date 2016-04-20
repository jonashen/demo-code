#ifndef OPER_STATEMENT_INCLUDED
#define OPER_STATEMENT_INCLUDED

#include "Statement.h"
#include "ProgramState.h"

class OperatorStatement: public Statement
{
private:
    std::string var; // name of this variable
    std::string other_var; // name of other variable (if provided)
    std::string sign_oper; // which operator is called upon
    int int_value; // value of the int provided
    
    
public:
    OperatorStatement(std::string var_name, int val, std::string sign);
    OperatorStatement(std::string var_name, std::string o_var, std::string sign);
    ~OperatorStatement();
    
    virtual void execute(ProgramState * state, std::ostream &outf);
};

#endif



