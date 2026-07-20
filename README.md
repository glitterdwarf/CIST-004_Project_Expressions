Current version's class instructions:
Objectives:
Solve problem, design solution and implement using C++ arrays
Learn how to manipulate multiple C++ arrays using the same indices
Use C++ stream to read in data and format output

Description:
Write a command-driven program named "ListExpressions" that will accept the following commands:
add
listall
listbyoperator
listsummary
exit

"add" command will read in the expression and save it away in the list
"listall" command will display all the expressions
"listbyoperator" command will read in the operator and display only expressions with that given operator
"listsummary" command will display the total number of expressions, the number expressions for each operator, the largest and smallest expression values
"exit" command will exit the program

Requirements:
1. The program must produce the same expected output as provided.
2. It must be using 3 arrays of data (operands and operator) to manage the list of Expression information. You can define the array of maximum size of 100.
4. There should be no global variables. Please use only local variables and parameters instead
5. Scanf and printf are not allowed (Please use C++ cin and cout and C++ formatting)
6. No multiple return statements/exit points in one function
7. Should handle error condition when the user enters invalid operators, invalid operand and invalid command.
8. It should display "There is no expression." when no expression is in the list.
9. When the user enters "listbyoperator" command and there is no matched expression, it should display "No expression is found with the operator: <search-operator>" message such as "No expression is found with the operator: $"
10. Each expression must be stored in these three arrays.
