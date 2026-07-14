#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

// Init func prototypes

// Menu Prototypes

int expMenu();
void process();

// Expression Entering and Validation

string enterExpression();
void newExpression(int[], int[], int[], char[], int&);
int expressionEvaluation(int, int, char);
bool expressionValidator(char, int);
bool operatorValidator(char);
void clearStream();

// Expression Displaying Prototypes

void displayExpression(int[], int[], int[], char[], const int&);
int numOpExp(char, const char[], const int&);
void listByOperator(int[], int[], int[], char[], const int&);
void listSummary(int[], char[], const int&);
int getSmallestResult(const int[], const int&);
int getLargestResult(const int[], const int&);

int main() {
    process();
    return 0;
}

////////////////// CORE MENU FUNCTIONS //////////////////

/* Process
 * Holds main function for each menu option
 * Input: Receives menu choice from perform()
 * Output: Calls function associated with each option
 */
void process() {
    int op1[100], op2[100], results[100];
    char mathOp[100];
    int numExpressions = 0;

    int menuChoice = 0;
    do {
        menuChoice = expMenu();
        switch (menuChoice) {
            case 1: newExpression(op1, op2, results, mathOp, numExpressions); break;
            case 2: displayExpression(op1, op2, results, mathOp, numExpressions); break;
            case 3: listByOperator(op1, op2, results, mathOp, numExpressions); break;
            case 4: listSummary(results, mathOp, numExpressions); break;
            case 5: cout << "Goodbye!" << endl; break;
            default:
                break;
        }
    } while (menuChoice != 5);
}

/* Menu
 * Displays menu options
 * Also displays program description
 * Input: User selects option
 * Output: Chosen option is retrieved by process()
 */
int expMenu() {
    cout << "======================================================" << endl
         << ">>>>>>>>>>>>>>>>>> EXPRESSION SAVER <<<<<<<<<<<<<<<<<<" << endl
         << "======================================================" << endl
        << "Select One (case-sensitive):" << endl
        << "   add" << endl
        << "   listall" << endl
        << "   listbyoperator" << endl
        << "   listsummary" << endl
        << "   exit" << endl
        << "======================================================" << endl << endl
        << "Enter your choice: ";
    string menuChoice;
    getline(cin, menuChoice);

    int choice = 0;
    if (menuChoice == "add")
        choice = 1;
    else if (menuChoice == "listall")
        choice = 2;
    else if (menuChoice == "listbyoperator")
        choice = 3;
    else if (menuChoice == "listsummary")
        choice = 4;
    else if (menuChoice == "exit")
        choice = 5;
    else {
        cout << "\nUnsupported command. Please try again." << endl;
    }
    return choice;
}

////////////////// SUPER FUN AND COMPLICATED ///////////////////////////////
///////////////// EXPRESSION SAVING AND PARSING FUNCTIONS //////////////////

string enterExpression() {
    cout << "======================================================" << endl
         << ">>>>>>>>>>>>>>>> ADD A NEW EXPRESSION <<<<<<<<<<<<<<<<" << endl
        << "Enter an integer, an operator, and another integer." << endl
        << "Choose from +, -, *, /, or %" << endl
        << "======================================================" << endl
        << "ENTER AN EXPRESSION: ";
    string newExpression;
    getline(cin, newExpression);
    if (cin.fail()) {
        clearStream();
    }
    return newExpression;
}

void newExpression(int op1[], int op2[], int results[], char mathOp[], int &numExpressions) {
    int operand1 = 0, operand2 = 0;
    char mathOperator;
    const string newExpression = enterExpression();
    stringstream ss(newExpression);
    ss >> operand1 >> mathOperator >> operand2;

    // Verify that the operand is valid and there is no division by zero
    if (const bool expressionValid = expressionValidator(mathOperator, operand2); ss.fail() || !expressionValid) {
        cout << "The expression is invalid." << endl << endl;
    } else {
        op1[numExpressions] = operand1;
        op2[numExpressions] = operand2;
        mathOp[numExpressions] = mathOperator;
        const int result = expressionEvaluation(op1[numExpressions], op2[numExpressions], mathOp[numExpressions]);
        results[numExpressions] = result;
        cout << "NEW EXPRESSION:" << endl << op1[numExpressions] << setw(10) <<
            mathOp[numExpressions] << setw(10) << op2[numExpressions] << setw(10)
            << "=" << setw(10) << results[numExpressions] << endl << endl;
        numExpressions++;
    }
}

bool operatorValidator(const char mathOperator) {
    bool operatorValid = false;
    if (mathOperator == '+' || mathOperator == '-' || mathOperator == '*' || mathOperator == '/' || mathOperator == '%') {
        operatorValid = true;
    }
    return operatorValid;
}

bool expressionValidator(const char mathOperator, const int operand2) {
    bool expressionValid;
    if (mathOperator == '+' || mathOperator == '-' || mathOperator == '*' || mathOperator == '/' || mathOperator == '%') {
        if (mathOperator == '/' && operand2 == 0) {
            expressionValid = false;
        } else {
            expressionValid = true;
        }
    } else {
        expressionValid = false;
    }
    return expressionValid;
}

int expressionEvaluation(const int operand1, const int operand2, const char mathOperator) {
    int result;
    switch (mathOperator) {
        case '-': result = operand1 - operand2; break;
        case '*': result = operand1 * operand2; break;
        case '/': result = operand1 / operand2; break;
        case '%': result = operand1 % operand2; break;
        default: result = operand1 + operand2; break;
    }
    return result;
}

////////////////// SIMPLE EXPRESSION RETRIEVAL FUNCTIONS //////////////////

/* Display Expression
 * Displays the current running list of all expressions saved by the user
 * Input: All arrays and the number of expressions
 * Output: All expressions
 */
void displayExpression(int op1[], int op2[], int results[], char mathOp[], const int &numExpressions) {
    cout << "======================================================" << endl
         << ">>>>>>>>>>>>>>>>>>> ALL EXPRESSIONS <<<<<<<<<<<<<<<<<<" << endl
         << "======================================================" << endl;
    if (numExpressions > 0) {
        for (int i = 0; i < numExpressions; i++) {
            cout << setw(10) << op1[i] << setw(10) << mathOp[i] << setw(10) <<
                    op2[i] << setw(10) << "=" << setw(10) << results[i] << endl;
        }
        cout << endl;
    } else {
        cout << "There are no expressions recorded yet." << endl << endl;
    }
}

/* List by Operator
 * Displays the list of expressions with matching operator
 * Input: All arrays and number of expressions
 * Output: Expression with matching operator
 */
void listByOperator(int op1[], int op2[], int results[], char mathOp[], const int &numExpressions) {
    cout << "======================================================" << endl
         << ">>>>>>>>>>>>>>>> DISPLAY BY OPERATOR <<<<<<<<<<<<<<<<<" << endl
         << "======================================================" << endl << endl;

    if (numExpressions > 0) {
        cout << "Enter an operator." << endl
        << "Choose from +, -, *, /, or %" << endl
        << "======================================================" << endl
        << "ENTER AN OPERATOR: ";
        char operatorChoice;
        cin >> operatorChoice;
        if (const bool operatorValid = operatorValidator(operatorChoice); cin.fail() || !operatorValid) {
            cout << "Invalid operator." << endl << endl;
        } else {
            clearStream();
            if (const int numOpExpSaved = numOpExp(operatorChoice, mathOp, numExpressions); numOpExpSaved > 0) {
                cout << "EXPRESSIONS WITH " << operatorChoice << ":" << endl;
                for (int i = 0; i < numExpressions; i++) {
                    if (mathOp[i] == operatorChoice) {
                        cout << setw(10) << op1[i] << setw(10) << mathOp[i] << setw(10) <<
                            op2[i] << setw(10) << "=" << setw(10) << results[i] << endl;
                    }
                }
                cout << endl << endl;
            } else {
                cout << "No expressions found with this operator: " << operatorChoice << endl << endl;
            }
        }
    } else {
        cout << "There are no expressions recorded yet." << endl << endl;
    }
}

/* List Summary
 * Summarizes the current array expressions by operator type, max and min
 * Input: Arrays
 * Output: Value saved in alias var largestExpression
 */
void listSummary(int results[], char mathOp[], const int &numExpressions) {
    cout << "======================================================" << endl
         << ">>>>>>>>>>>>>>>>>>> LIST SUMMARY <<<<<<<<<<<<<<<<<<<<<" << endl
         << "======================================================" << endl << endl;
    if (numExpressions > 0) {
        // Get count for expressions by operator
        const int addExp = numOpExp('+', mathOp, numExpressions);
        const int subExp = numOpExp('-', mathOp, numExpressions);
        const int multExp = numOpExp('*', mathOp, numExpressions);
        const int divExp = numOpExp('/', mathOp, numExpressions);
        const int modExp = numOpExp('%', mathOp, numExpressions);

        const int smallestExp = getSmallestResult(results, numExpressions);
        const int largestExp = getLargestResult(results, numExpressions);

        cout << setw(32) << left << "TOTAL NUMBER OF EXPRESSIONS: " << numExpressions << endl
            << setw(32) << "NUMBER OF + EXPRESSIONS: " << addExp << endl
            << setw(32) << "NUMBER OF - EXPRESSIONS:" << subExp << endl
            << setw(32) << "NUMBER OF * EXPRESSIONS:" << multExp << endl
            << setw(32) << "NUMBER OF / EXPRESSIONS:" << divExp << endl
            << setw(32) << "NUMBER OF % EXPRESSIONS:" << modExp << endl
            << setw(32) << "LARGEST EXPRESSIONS:" << largestExp << endl
            << setw(32) << "SMALLEST EXPRESSIONS:" << smallestExp << endl << endl;
    } else {
        cout << "There are no expressions recorded yet." << endl << endl;
    }
}

/* Num Expressions
 *  Count how many saved expressions match the chosen operator
 *  Input: Operator array, chosen operator, and total number of expressions
 *  Output: Number of expressions using chosen operator
 */
int numOpExp(const char operatorChoice, const char mathOp[], const int &numExpressions) {
    int numOpExp = 0;
    for (int i = 0; i < numExpressions; i++) {
        if (operatorChoice == mathOp[i]) {
            numOpExp++;
        }
    }
    return numOpExp;
}

/* Get Largest Result
 * Loops through results array to find the largest value
 * Input: Results array, number of expressions
 * Output: Largest expression result
 */
int getLargestResult(const int results[], const int &numExpressions) {
    int largestExp = results[0];
    for (int i = 0; i < numExpressions; i++) {
        if (results[i] > largestExp) {
            largestExp = results[i];
        }
    }
    return largestExp;
}

/* Get Smallest Result
 * Loops through results array to find the smallest value
 * Input: Results array, number of expressions
 * Output: Smallest expression result
 */
int getSmallestResult(const int results[], const int &numExpressions) {
    int smallestExp = results[0];
    for (int i = 0; i < numExpressions; i++) {
        if (results[i] < smallestExp) {
            smallestExp = results[i];
        }
    }
    return smallestExp;
}

/* Clear Stream
 * Performs cin.clear and cin.ignore as needed
 */
void clearStream() {
    cin.clear();
    cin.ignore(INT_MAX, '\n');
}