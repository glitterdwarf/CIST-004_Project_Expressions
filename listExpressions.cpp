#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

class Expression {
private:
    int m_operand1;
    int m_operand2;
    char m_mathOperator;

public:
    Expression(const int operand1, const int operand2, const char mathOperator) : m_operand1(operand1),
        m_operand2(operand2), m_mathOperator(mathOperator) {
    };

    // Getters

    string toString() const {
        stringstream ss;
        ss << setw(10) << m_operand1 << setw(10) << m_mathOperator << setw(10) << m_operand2 <<
                setw(10) << "=" << setw(10) << this->getResult();
        return ss.str();
    };

    bool isEqual(const Expression &another) const {
        return (m_operand1 == another.m_operand1 && m_operand2 == another.m_operand2
                && m_mathOperator == another.m_mathOperator);
    };

    char getOperator() const {
        return m_mathOperator;
    }

    // Setters

    int getResult() const {
        int result = 0;
        switch (m_mathOperator) {
            case '+': result = m_operand1 + m_operand2;
                break;
            case '-': result = m_operand1 - m_operand2;
                break;
            case '*': result = m_operand1 * m_operand2;
                break;
            case '/': result = m_operand1 / m_operand2;
                break;
            case '%': result = m_operand1 % m_operand2;
                break;
            default: break;
        }
        return result;
    }
};

// Init func

int expressionTest(Expression *[]);

// Menu Prototypes

int expMenu();

void process();

// Expression Entering and Validation

string enterExpression();

void newExpression(Expression *[], int &);

bool expressionValidator(char, int);

bool operatorValidator(char);

void deleteExpression(Expression *expressionArray[], const int &);

void clearStream();

void clearArray(Expression *expressionArray[], const int &);

// Expression Displaying Prototypes

void displayExpression(Expression *[], const int &);

int numOpExp(char, Expression *[], const int &);

void listByOperator(Expression *[], const int &);

void listSummary(Expression *[], const int &);

int main() {
    process();
    return 0;
}

////////////////// TESTING FUNCTIONS //////////////////

int expressionTest(Expression *expressionArray[]) {
    int numExpressions = 0;

    for (int i = 0; i < 7; i++, numExpressions++) {
        const Expression testExp[] = {
            {10, 20, '+'},
            {1, 0, '*'},
            {9, 5, '*'},
            {201, 1, '-'},
            {11, 3, '%'},
            {1, 2, '%'},
            {1, 0, '*'}
        };
        auto *testExpression = new Expression(testExp[i]);
        expressionArray[i] = testExpression;
    }

    return numExpressions;
}

////////////////// CORE MENU FUNCTIONS //////////////////

/* Process
 * Holds main function for each menu option
 * Input: Receives menu choice from perform()
 * Output: Calls function associated with each option
 */
void process() {
    int numExpressions = 0;
    Expression *expressionArray[1000];

    cout << "///// ADD TEST VALUES? /////" << endl << "0 for no, 1 for yes: ";
    bool testMode = false;
    cin >> testMode;
    clearStream();
    if (testMode) {
        cout << "Adding default testing expressions" << endl << endl << endl;
        numExpressions = expressionTest(expressionArray);
    }

    int menuChoice = 0;
    do {
        menuChoice = expMenu();
        switch (menuChoice) {
            case 1: newExpression(expressionArray, numExpressions);
                break;
            case 2: deleteExpression(expressionArray, numExpressions);
                break;
            case 3: displayExpression(expressionArray, numExpressions);
                break;
            case 4: listByOperator(expressionArray, numExpressions);
                break;
            case 5: listSummary(expressionArray, numExpressions);
                break;
            case 6: cout << "Goodbye!" << endl;
                clearArray(expressionArray, numExpressions);
                break;
            default:
                break;
        }
    } while (menuChoice != 6);
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
            << "Select One (case-sensitive): add, delete, listall, listbyoperator, listsummary, exit" << endl
            << "Enter your choice: ";
    string menuChoice;
    getline(cin, menuChoice);

    int choice = 0;
    if (menuChoice == "add")
        choice = 1;
    else if (menuChoice == "delete")
        choice = 2;
    else if (menuChoice == "listall")
        choice = 3;
    else if (menuChoice == "listbyoperator")
        choice = 4;
    else if (menuChoice == "listsummary")
        choice = 5;
    else if (menuChoice == "exit")
        choice = 6;
    else {
        cout << "\nUnsupported command. Please try again." << endl;
    }
    return choice;
}

///////////////// EXPRESSION SAVING AND PARSING FUNCTIONS //////////////////

/* Enter Expression
 * Menu prompt that accepts user input to add expressions one-by-one
 * Input: User prompt in the form of int1 operand int2
 * Output: Returns this cin input to "newExpression" caller for processing
 */
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

/* New Expression
 * Caller and processor for new expressions added manually by user input.
 * Input: Calls enterExpression() and retrieves user input.
 * Output:
 *      Internal:
 *          Creates new Expression object and pointer to that expression, which is then added to the
 *          expression pointer array
 *          Adds to numExpressions variable
 *      External:
 *          Tells user if expression was invalid.
 *          If valid, prints the expressions including the computed result.
 */
void newExpression(Expression *expressionArray[], int &numExpressions) {
    int operand1 = 0, operand2 = 0;
    char mathOperator;
    const string newExpression = enterExpression();
    stringstream ss(newExpression);
    ss >> operand1 >> mathOperator >> operand2;

    // Verify that the operand is valid and there is no division by zero
    if (const bool expressionValid = expressionValidator(mathOperator, operand2); ss.fail() || !expressionValid) {
        cout << "The expression is invalid." << endl << endl;
    } else {
        stringstream ss2;
        ss << "exp" << numExpressions;
        string expName = ss.str();
        auto *newExp = new Expression(operand1, operand2, mathOperator);
        expressionArray[numExpressions] = newExp;
        cout << "NEW EXPRESSION:" << endl << newExp->toString() << endl << endl;
        numExpressions++;
    }
}

/* Operator Validator
 * Checks if the entered math operator is one of the approved entries. Unlike expressionValidator(),
 * operatorValidator() does not also check if the expression can be performed.
 * Input: Call from listByOperator(), including user entered math operator
 * Output: Returns boolean value to listByOperator() indicating if the operator is allowed or not.
 */
bool operatorValidator(const char mathOperator) {
    bool operatorValid = false;
    if (mathOperator == '+' || mathOperator == '-' || mathOperator == '*' || mathOperator == '/' || mathOperator ==
        '%') {
        operatorValid = true;
    }
    return operatorValid;
}

/* Expression Validator
 * Verifies if the expression as entered can be performed.
 * Input: User input from caller newExpression()
 * Output: Boolean value indicating if the expression is valid.
 *         If the operand isn't '+', '-', '*', '/', or '%', returns false.
 *         If the operand is '/' AND the second integer is '0', returns false.
 *         Otherwise, returns true.
 */
bool expressionValidator(const char mathOperator, const int operand2) {
    bool expressionValid;
    if (mathOperator == '+' || mathOperator == '-' || mathOperator == '*' || mathOperator == '/' || mathOperator ==
        '%') {
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

////////////////// SIMPLE EXPRESSION RETRIEVAL FUNCTIONS //////////////////

/* Delete Expression
 * Adds the option for a user to delete an expression from the array
 * Input: string entry from user
 * Output: Internal:
 *              Pointers are deleted to free up memory and are set to nullptr.
 *         External:
 *              If no expressions matched, lets the user know none existed.
 *              Otherwise, prints that deletion was successful.
 *              If >1 expressions were found and deleted, also outputs number of deletions.
 */
void deleteExpression(Expression *expressionArray[], const int &numExpressions) {
    int operand1 = 0, operand2 = 0, numDeleted = 0;
    char mathOperator = ' ';

    cout << "======================================================" << endl
            << ">>>>>>>>>>>>>>>> DELETE EXPRESSION <<<<<<<<<<<<<<<<" << endl
            << "Enter the expression you want to be deleted." << endl
            << "======================================================" << endl
            << "ENTER AN EXPRESSION: ";
    string newExpression;
    getline(cin, newExpression);
    if (cin.fail()) {
        clearStream();
    }
    stringstream ss(newExpression);
    ss >> operand1 >> mathOperator >> operand2;

    const Expression tempExpression(operand1, operand2, mathOperator);

    for (int i = 0; i < numExpressions; i++) {
        if (expressionArray[i] != nullptr && (expressionArray[i]->isEqual(tempExpression))) {
            delete expressionArray[i];
            expressionArray[i] = nullptr;
            numDeleted++;
        }
    }

    if (numDeleted != 0) {
        if (numDeleted == 1) {
            cout << "Matching expression deleted." << endl << endl;
        } else {
            cout << numDeleted << " matching expressions deleted." << endl << endl;
        }
    } else {
        cout << "No matching expressions were found." << endl << endl;
    }
}

/* Display Expression
 * Displays the current running list of all expressions saved by the user
 * Input: All arrays and the number of expressions
 * Output: All expressions
 */
void displayExpression(Expression *expressionArray[], const int &numExpressions) {
    cout << "======================================================" << endl
            << ">>>>>>>>>>>>>>>>>>> ALL EXPRESSIONS <<<<<<<<<<<<<<<<<<" << endl
            << "======================================================" << endl;
    if (numExpressions > 0) {
        for (int i = 0; i < numExpressions; i++) {
            if (expressionArray[i] != nullptr) {
                cout << expressionArray[i]->toString() << endl;
            }
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
void listByOperator(Expression *expressionArray[], const int &numExpressions) {
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
            if (const int numOpExpSaved = numOpExp(operatorChoice, expressionArray, numExpressions);
                numOpExpSaved > 0) {
                cout << "EXPRESSIONS WITH " << operatorChoice << ":" << endl;
                for (int i = 0; i < numExpressions; i++) {
                    if (expressionArray[i] != nullptr && (expressionArray[i]->getOperator() == operatorChoice)) {
                        cout << expressionArray[i]->toString() << endl;
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
void listSummary(Expression *expressionArray[], const int &numExpressions) {
    cout << "======================================================" << endl
            << ">>>>>>>>>>>>>>>>>>> LIST SUMMARY <<<<<<<<<<<<<<<<<<<<<" << endl
            << "======================================================" << endl << endl;
    if (numExpressions > 0) {
        // Count number of non-deleted expressions
        int numActiveExpressions = 0;
        int addExp = 0, subExp = 0, multExp = 0, divExp = 0, modExp = 0, smallestExp = 0, largestExp = 0;

        for (int i = 0; i < numExpressions; i++) {
            if (expressionArray[i] != nullptr) {
                if (expressionArray[i]->getOperator() == '+') {
                    addExp++;
                } else if (expressionArray[i]->getOperator() == '-') {
                    subExp++;
                } else if (expressionArray[i]->getOperator() == '*') {
                    multExp++;
                } else if (expressionArray[i]->getOperator() == '/') {
                    divExp++;
                } else if (expressionArray[i]->getOperator() == '%') {
                    modExp++;
                }
                if (expressionArray[i]->getResult() < smallestExp) {
                    smallestExp = expressionArray[i]->getResult();
                }
                if (expressionArray[i]->getResult() > largestExp) {
                    largestExp = expressionArray[i]->getResult();
                }
                numActiveExpressions++;
            }
        }

        cout << setw(32) << left << "TOTAL NUMBER OF EXPRESSIONS: " << numActiveExpressions << endl
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
int numOpExp(const char operatorChoice, Expression *expressionArray[], const int &numExpressions) {
    int numOpExp = 0;
    for (int i = 0; i < numExpressions; i++) {
        if (expressionArray[i] != nullptr && (expressionArray[i]->getOperator() == operatorChoice)) {
            numOpExp++;
        }
    }
    return numOpExp;
}

/* Clear Stream
 * Performs cin.clear and cin.ignore as needed
 */
void clearStream() {
    cin.clear();
    cin.ignore(INT_MAX, '\n');
}

/* Clear Array
 * Deletes all dynamically allocalted memory at the end of the program.
 * Input: Array of expression pointers
 * Output: Deletes pointers and sets their value to nullptr
 */
void clearArray(Expression *expressionArray[], const int &numExpressions) {
    for (int i = 0; i < numExpressions; i++) {
        delete expressionArray[i];
        expressionArray[i] = nullptr;
    }
    delete expressionArray;
    expressionArray = nullptr;
}