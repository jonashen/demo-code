// IfStatement.cpp:
#include "../lib/IfStatement.h"
using namespace std;

IfStatement::IfStatement(string var, string op, int val, int line)
: var_name( var ), ovar_name(""), op_name( op ), value( val ),
line_num( line ), is_true( false )
{
}

IfStatement::IfStatement(string var, string op, string o_var, int line)
: var_name( var ), ovar_name( o_var ), op_name( op ), value( 0 ),
line_num( line ), is_true( false )
{
}

IfStatement::~IfStatement()
{
}

void IfStatement::execute(ProgramState * state, ostream &outf)
{
    if( line_num <= 0 || line_num > state->numLines() ) // Line not in boundaries of program
    {
        outf << "Illegal jump instruction\n";
        state->set_line( state->numLines() ); // Jumps to last line
    }
    
    else
    {
        /* These are used to implement switch cases
         * 1 = Less than                    <
         * 2 = Greater Than                 >
         * 3 = Equal To                     =
         * 4 = Less Than Or Equal To        <=
         * 5 = Greater Than or Equal To     =>
         * 6 = Not Equal To                 <>
         */
        if (op_name == "<")
            op_val = 1;
        
        else if (op_name == ">")
            op_val = 2;
        
        else if (op_name == "=")
            op_val = 3;
        
        else if (op_name == "<=")
            op_val = 4;
        
        else if (op_name == ">=")
            op_val = 5;
        
        else if (op_name == "<>")
            op_val = 6;
        
        // If variable is provided instead of an int, saves its value
        if( ovar_name != "" )
            value = state->get_val( ovar_name );
        
        
        switch (op_val) // depends on the operator
        {
            case 1: // Less than
                if( state->get_val(var_name) < value )
                    is_true = true;
                break;
                
            case 2: // Greater than
                if( state->get_val(var_name) > value )
                    is_true = true;
                break;
                
            case 3: // Equal To
                if( state->get_val(var_name) == value )
                    is_true = true;
                break;
                
            case 4: // Less Than or Equal To
                if( state->get_val(var_name) <= value )
                    is_true = true;
                break;
                
            case 5: // Greater Than or Equal To
                if( state->get_val(var_name) >= value )
                    is_true = true;
                break;
                
            case 6: // Not equal to
                if( state->get_val(var_name) != value )
                    is_true = true;
                break;
        }
        
        if ( is_true ) // If comparison is true
            state->set_line( line_num ); // Jumps to line provided
        
        else
            state->nextLine();
    }
}