#include "../lib/GoStatement.h"
using namespace std;

GoStatement::GoStatement(int num, string type)
: line_num( num ), go_type( type )
{
}

GoStatement::~GoStatement()
{
}

void GoStatement::execute(ProgramState * state, ostream &outf)
{
    if( line_num < 0 || line_num > state->numLines() ) // Line not in boundaries of program
    {
        outf << "Illegal jump instruction\n";
        state->set_line( state->numLines() ); // Jumps to last line
    }
    
    
    else if (go_type == "GOTO") // GOTO
    {
        state->set_line( line_num );
    }
    
    else // GOSUB or RETURN
    {
        if (go_type == "GOSUB") // GOSUB
        {
            state->gosub_stack()->push( state->currLine() + 1 ); // saves the next line as a "bookmark"
            state->set_line( line_num ); // jumps to the line number
        }
        
        else // RETURN
        {
            if ( !state->gosub_stack()->empty() ) // if the stack is not empty
            {
                state->set_line( state->gosub_stack()->top() ); // returns to previously saved line number
                state->gosub_stack()->pop(); // deletes the bookmark from the stack
            }
            
            else // if the stack is empty, acts as EndStatement
                state->set_line( state->numLines() ); // jumps to the last line
        }
    }
}