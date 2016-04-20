#ifndef GO_STATEMENT_INCLUDED
#define GO_STATEMENT_INCLUDED

#include "Statement.h"
#include "ProgramState.h"
#include "stackint.h"
#include <iostream>

class GoStatement: public Statement
{
private:
    int line_num;
    std::string go_type;
    
public:
    GoStatement(int num, std::string type);
    ~GoStatement();
    
    virtual void execute(ProgramState * state, std::ostream &outf);
};

#endif

