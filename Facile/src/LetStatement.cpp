// LetStatement.cpp:
#include "../lib/LetStatement.h"
using namespace std;

LetStatement::LetStatement(string variableName, int value)
	: m_variableName( variableName ), m_value( value )
{
}

LetStatement::~LetStatement()
{
}

// The LetStatement version of execute() should make two changes to the
// state of the program:
//
//    * set the value of the appropriate variable
//    * increment the program counter
void LetStatement::execute(ProgramState * state, ostream &outf)
{
    state->set_var(m_variableName, m_value);
    state->nextLine();
}