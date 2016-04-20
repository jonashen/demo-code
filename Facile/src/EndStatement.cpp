// EndStatement.cpp:
#include "../lib/EndStatement.h"
using namespace std;

EndStatement::EndStatement()
{
}

EndStatement::~EndStatement()
{
}

void EndStatement::execute(ProgramState * state, ostream &outf)
{
    // Sets current line to last line
    state->set_line( state->numLines() );
}
