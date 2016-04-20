## Synopsis

This is an Interpretor and Debugger for a simple Facile programming language, built with a GUI interface using the Qt framework.

## Code Example
LET *var* *int*  | Change the value of variable *var* to the integer *int*

PRINT *var*      | Print the value of variable *var* to output

PRINTALL         | Prints the value of all used variables to output, one per line.

ADD *var* *p*    | Adds *p* to the value of the variable *var*, where *p* is an int or variable.

SUB *var* *p*    | Subtracts *p* from  the value of the variable *var*, where *p* is an int or variable.

MULT *var* *p*   | Multiplies the value of the variable *var* by the integer or variable *p*

DIV *var* *p*    | Divides the value of the variable *var* by the integer or variable *p*

GOTO *linenum*   | Jumps execution of the program to the line numbered *linenum*

IF *var* *op*    | Compares the value of the variable *var* to the integer *int*

*int* THEN       | via the operator *op* (<, <=, >, >=, =, <>), and jumps

*linenum*        | execution of the program to line *linenum* if true.


GOSUB *linenum*  | Temporarily jumps to line *linenum*, and jumps back after a RETURN

RETURN           | Jumps execution of the program back to the most recently executed GOSUB.

END              | Immediately terminates the program.

.                | Placed at the end of the program, and behaves like an END statement.

## Installation

Type "make all" into the console and "./Facile" to run the program.
Type "make clean" to remove all binary files in bin/ and the Facile program.

## Tests

Example 1:

LET KYLO 1

GOSUB 7

PRINT KYLO

END

LET KYLO 3

RETURN

PRINT KYLO

LET KYLO 2

GOSUB 5

PRINT KYLO

RETURN

.

Output:

1

3

3


Example 2:

PRINT A

PRINTALL
.

Output:

0

A 0 // This line does not show up because A has not been declared with "LET"

## Contributors

Jonathon Shen

## License

© Jonathon Shen
