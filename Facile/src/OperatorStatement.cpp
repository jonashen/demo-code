#include "../lib/OperatorStatement.h"
using namespace std;

OperatorStatement::OperatorStatement(string var_name, int val, string sign)
: var( var_name ), other_var( "" ), sign_oper( sign ), int_value( val )
{
} // if p is digit

OperatorStatement::OperatorStatement(string var_name, string o_var, string sign)
: var( var_name ), other_var( o_var ), sign_oper( sign ), int_value( 0 )
{
} // if p is a variable

OperatorStatement::~OperatorStatement()
{
}

void OperatorStatement::execute(ProgramState * state, ostream &outf)
{
    if (sign_oper == "ADD") // +
    {
        if( other_var.empty() ) // p is a digit
            state->set_var( var, state->get_val(var) + int_value );
        
        else // p is a variable
            state->set_var( var, state->get_val(var) + state->get_val(other_var) );
        
        state->nextLine();
    }
    
    else if (sign_oper == "SUB") // -
    {
        if( other_var.empty() ) // p is a digit
            state->set_var( var, state->get_val(var) - int_value );
        
        else
            state->set_var( var, state->get_val(var) - state->get_val(other_var) );
        
        state->nextLine();
    }
    
    else if (sign_oper == "MULT") // *
    {
        if( other_var.empty() ) // p is a digit
            state->set_var( var, state->get_val(var) * int_value );
        
        else
            state->set_var( var, state->get_val(var) * state->get_val(other_var) );
        
        state->nextLine();
    }
    
    else if (sign_oper == "DIV") // /
    {
        if( other_var.empty() ) // p is a digit
        {
            if ( int_value == 0 ) // trying to divide by zero
            {
                outf << "Divide by zero exception\n";
                state->set_zero(true);
            }
            
            else
                state->set_var( var, state->get_val(var) / int_value );
        }
        
        else
            state->set_var( var, state->get_val(var) / state->get_val(other_var) );
        
        state->nextLine();
    }
}
