#include "../lib/ProgramState.h"

// Constructor
ProgramState::ProgramState(int numLines)
{
    num_lines = numLines;
    curr_line = 1; // Start with line 1
}

// Returns total line numbers in the program
int ProgramState::numLines()
{
    return num_lines;
}

// Returns the current line number in the program
int ProgramState::currLine()
{
    return curr_line;
}

// Increments the program counter
void ProgramState::nextLine()
{
    curr_line++;
}

// Checks if last line of program ???
bool ProgramState::end()
{
    return curr_line == num_lines;
}

// Sets current line
void ProgramState::set_line(int line)
{
    curr_line = line;
}

// Returns the value of the variable
int ProgramState::get_val(std::string var)
{
    std::map<std::string, int>::iterator it;
    
    it = values.find(var);
    return it->second;
}

// Adds a new variable and its value into map, else rewrites value
void ProgramState::set_var(std::string var, int val)
{
    values[var] = val;
}

// Returns a pointer to the gosub_lines stack
StackInt * ProgramState::gosub_stack()
{
    return &gosub_lines;
}

// Returns a pointer to the values map
std::map<std::string, int> * ProgramState::var_map()
{
     return &values;
}

// Changes if tried to divide by zero
void ProgramState::set_zero(bool t)
{
    divide_by_zero = t;
}

// Checks if tried to divide by zero
bool ProgramState::get_zero()
{
    return divide_by_zero;
}
