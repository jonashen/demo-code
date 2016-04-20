// ProgramState.h
//
// CS 104 / Spring 2016
//
// The ProgramState class encapsulates the state of an executing Facile
// program.  The state of a Facile program consists of three parts:
//
//    * The program counter, which specifies the line number of the
//      statement that will execute next.
//    * An array of 26 integers, holding the current values of the 26
//      variables.
//    * A stack of integers, which is used to hold return lines for GOSUB
//      statements.
//
// I've provided you a start on this class, but you'll need to add methods
// to it as you go along.  In particular, you'll need methods to access and
// modify the state; these methods will be called primarily by the various
// execute() methods in the Statement subclasses, to allow the execution of
// a statement to change the state of a program.  For example, executing a
// GOTO statement will cause the program counter to be changed.

#ifndef PROGRAM_STATE_INCLUDED
#define PROGRAM_STATE_INCLUDED

#include "stackint.h"
#include <string>
#include <map>

class ProgramState
{
public:
	ProgramState(int numLines);

	// You'll need to add a variety of methods here.  Rather than trying to
	// think of what you'll need to add ahead of time, add them as you find
	// that you need them.
    
    // Returns total line numbers in the program
    int numLines();
    
    // Returns the current line number in the program
    int currLine();
    
    // Increments the program counter
    void nextLine();
    
    // Checks if last line of program ???
    bool end();
    
    // Sets current line
    void set_line(int line);
    
    // Returns the value of a variable
    int get_val(std::string var);
    
    // Adds a new variable and its value into map, else rewrites value
    void set_var(std::string var, int val);
    
    // Returns a pointer to the gosub_lines stack
    StackInt * gosub_stack();
    
    // Returns a pointer to the values map
    std::map<std::string, int> * var_map();
    
    // Changes if tried to divide by zero
    void set_zero(bool t);
    
    // Checks if tried to divide by zero
    bool get_zero();


private:
    bool divide_by_zero; // did someone divide by zero
    int num_lines;
    int curr_line;
    std::map <std::string, int> values;
    StackInt gosub_lines;
};

#endif



