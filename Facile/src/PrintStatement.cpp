// PrintStatement.cpp:
#include "../lib/PrintStatement.h"
using namespace std;

PrintStatement::PrintStatement(string variableName)
: m_variableName( variableName )
{
}

PrintStatement::~PrintStatement()
{
}

void PrintStatement::execute(ProgramState * state, ostream &outf)
{
    if (m_variableName == "ALL") // PRINTALL
    {
        map<string, int> * vars = state->var_map();
        
        for(map<string, int>::const_iterator it = vars->begin();
            it != vars->end(); ++it)
        {
            outf << it->first << " " << it->second << "\n";
        }
        state->nextLine();
    }
    
    else // PRINT
    {
        outf << state->get_val( m_variableName ) << "\n";
        state->nextLine();
    }
}