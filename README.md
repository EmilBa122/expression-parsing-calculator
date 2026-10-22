# expression-parsing-calculator

## Assignment Description
Parsing and Evaluating Arithmetic Expressions with Nested Parentheses in C

A command-line calculator, similar to a small part of the Linux `bc` program, that reads arithmetic expressions line by line from standard input 
and prints the result of each one. It supports:

- Addition, subtraction and multiplication between positive and negative integers (e.g. `-25 * 4 - 7`), with correct operator precedence
(multiplication before addition and subtraction, left-to-right evaluation)
- Nested parentheses at any depth, starting the evaluation from the innermost and moving to the outermost (e.g. `((-3 + 8) * (7 + 2)) - 5`)
- Spaces and tabs between numbers and operators
- Error detection with specific messages (wrong character, unexpected character, unexpected end of input, missing closing parenthesis), after
which the program continues with the next expression

The program reads the input one character at a time with `getchar()`, without using arrays or strings, as required by the assignment.
