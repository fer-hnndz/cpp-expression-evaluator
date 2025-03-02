#include <iostream>
#include <map>
#include <print>
#include <stack>
#include <stdexcept>
#include <vector>

#include "configparser.h"
#include "evaluator.h"

/**
 * ===========================
 * Debug Prints
 * ============================
 */

void Evaluator::printStacks(std::stack<char> operators, const std::vector<std::string> terms) {
  std::print("Operators: ");

  while (!operators.empty()) {
    std::print("{}, ", operators.top());
    operators.pop();
  }

  std::print("\nOperands: ");
  for (std::string op : terms) {
    std::print("{}, ", op);
  }
  std::print("\n");
}

void Evaluator::printPostfixExpression(std::stack<char> operators, const std::vector<std::string> terms) {

  // Print the Operators and Terms as is.
  printStacks(operators, terms);

  // Print in postfix syntax.

  std::print("Postfix Syntax: ");

  for (std::string operand : terms) {
    std::print("{}, ", operand);
  }

  while (!operators.empty()) {
    if (operators.size() == 1) {
      std::print("{}\n", operators.top());
      break;
    }

    std::print("{}, ", operators.top());
    operators.pop();
  }
  std::print("\n---\n");
}

/*
  ============
  Constructors
  ============
*/

/**
 * Creates a new Evaluator object.
 *
 * @param constants (`ConfigParser`) The constants to use in the evaluation.
 */
Evaluator::Evaluator(ConfigParser *constants) { this->constants = constants; };

/**
 * Creates a new Evaluator object.
 */
Evaluator::Evaluator() { this->constants = nullptr; };

Evaluator::~Evaluator() {};

/*
  =================
  Parsing Functions
  ==================
*/

/**
 * Transforms the operators between parentheses to terms into the terms vector.
 * @throws std::invalid_argument If no opening parenthesis is found.
 */
void Evaluator::parenthesesToTerm() {
  if (operators.empty())
    throw std::invalid_argument("Invalid expression: No opening parenthesis found.");

  while (operators.size() > 0) {
    if (operators.top() == '(') {
      operators.pop(); // Remove the `(`.
      return;
    }

    // Push all the operators to the terms list.
    terms.push_back(std::string(1, operators.top()));
    operators.pop();
  }

  throw std::invalid_argument("Invalid expression: No opening parenthesis found.");
}

/**
 * Stores the term on the terms list and automatically clears the termm buffer.
 *
 * @param term The term to push to the terms list.
 * @param terms The list of terms
 */
void Evaluator::pushTerm(std::string &termBuffer) {
  if (termBuffer.empty())
    return;

  terms.push_back(termBuffer);
  termBuffer = "";
}

/**
 * Iterates over all tokens and populates the `terms` vector and `operators` stack.
 */
void Evaluator::iterateTokens() {
  std::string termBuffer = "";
  bool hasDotAlready = false;

  for (int i = 0; i < expression.length(); i++) {
    char currentToken = expression.at(i);

    if (currentToken == ' ') {
      hasDotAlready = false;
      pushTerm(termBuffer);
      continue;
    }

    bool isValidAlphaNumeric = (isalnum(currentToken) || currentToken == '.') && !mgr.isValidOperator(currentToken);
    if (isValidAlphaNumeric) {

      if (termBuffer.empty()) {
        // Accept either since we don't have a a term in the buffer.
        termBuffer += currentToken;
        continue;
      }

      bool termIsNumber = isdigit(termBuffer.at(0));

      if (!termIsNumber) {
        // A variable can have any alphanumeric on it. Just append it.

        termBuffer += currentToken;
        continue;
      }

      // Here we have a number

      // Don't accept two dots (.) in a number.
      if (hasDotAlready && currentToken == '.')
        throw std::invalid_argument("Invalid number format: Multiple dots found in "
                                    "number.");

      // Only accept numbers if the stored term starts with a number.
      if (!isdigit(currentToken) && currentToken != '.')
        throw std::invalid_argument("Invalid number format: Non-digit character " + std::string(1, currentToken) +
                                    " found in number " + termBuffer + ".");

      if (currentToken == '.')
        hasDotAlready = true;

      termBuffer += currentToken;

      // End of alphanumeric checks
      continue;
    }

    // When code reaches here, we are supposed to handle an operator.
    hasDotAlready = false;
    pushTerm(termBuffer);

    handleOperator(currentToken);
  }

  // Push the last term if it exists.
  pushTerm(termBuffer);
}

/**
 * Handles the insertion of the specified operator onto the operator stack.
 *
 * @param op (`char`) The operator to insert.
 *
 * @throws `std::invalid_argument` The specified operator is not a valid operator.
 */
void Evaluator::handleOperator(char op) {

  if (!mgr.isValidOperator(op))
    throw std::invalid_argument("Invalid operator found: " + std::string(1, op));

  // Avoid closing parentheses to allow for operations like 10 + (1) = 11.
  if ((operators.empty() || op == '(' || operators.top() == '(') && op != ')') {
    operators.push(op);
    return;
  }

  if (op == ')') {
    parenthesesToTerm();
    return;
  }

  // Parse normally the operators
  int currentPrecedence = mgr.getOperatorPrecedence(op);
  int stackPrecedence = mgr.getOperatorPrecedence(operators.top());

  if (currentPrecedence >= stackPrecedence) {
    char lastOperator = operators.top();

    operators.pop();
    terms.push_back(std::string(1, lastOperator));
    operators.push(op);

  } else
    operators.push(op);
}

/*
  ========
  Entries
  ========
*/

/**
 * Entry point for the Evaluator's parsing.
 * Calls `iterateTokens` to populate the stacks, prints debug output if `debug`
 * is set to `true` and evaluates the expression.
 */
std::expected<float, std::string> Evaluator::readExpression() {
  bool hasDotAlready = false;
  iterateTokens();

  if (debug)
    printPostfixExpression(operators, terms);

  auto r = evaluateExpression();
  return 0;
  ;
}

/**
 * Iterates over the terms and operators data structures and operates the terms.
 * Asks for any variable value if needed.
 */
std::expected<float, std::string> Evaluator::evaluateExpression() {
  std::stack<float> evaluationStack;
  std::map<std::string, float> variables;

  // Add numbers to the evaluation stack until an operator in the operands is
  // found.

  for (int i = 0; i < terms.size(); i++) {
    std::string currentTerm = terms.at(i);

    bool isTerm = !mgr.isValidOperator(currentTerm.at(0)) && (isalpha(currentTerm.at(0)) || isdigit(currentTerm.at(0)));

    if (isTerm) {

      // Check if its a digit
      if (isdigit(currentTerm.at(0))) {
        evaluationStack.push(std::stof(currentTerm));
        continue;
      }

      // Check if it's a constant defined in the setting

      if (constants != nullptr && constants->get(currentTerm) != nullptr) {
        float *val = constants->get(currentTerm);
        evaluationStack.push(*val);

        continue;
      }

      // Ask for the value of the variable if it's not in the variables map.
      if (variables.find(currentTerm) == variables.end()) {
        std::print("Enter the value of the variable `{}`: ", currentTerm);
        std::string val = "";
        std::cin >> val;

        try {
          variables[currentTerm] = std::stof(val);
        } catch (std::exception &e) {

          // Show a custom message
          throw std::runtime_error("Cannot map `float` value " + val + " to term `" + currentTerm + "`.");
        }
      }

      evaluationStack.push(variables[currentTerm]);
      continue;
    }

    // Here we have detected an operation in the terms stack.
    // Possibly from a parentheses term.

    if (evaluationStack.size() < 2)
      throw std::invalid_argument("Invalid expression: Not enough terms to operate.");

    float rightNum = evaluationStack.top();
    evaluationStack.pop();
    float leftNum = evaluationStack.top();
    evaluationStack.pop();

    float result = mgr.operate(leftNum, rightNum, currentTerm.at(0));
    evaluationStack.push(result);
  }

  // Finished iterating over the operands (so we process any operator located
  // there) Process now the operator stack
  while (!operators.empty()) {

    if (operators.top() == '(')
      throw std::invalid_argument("Invalid expression: No closing parenthesis found.");

    if (evaluationStack.size() < 2)
      throw std::invalid_argument("Invalid expression: Not enough terms to operate.");

    float rightNum = evaluationStack.top();
    evaluationStack.pop();
    float leftNum = evaluationStack.top();
    evaluationStack.pop();

    evaluationStack.push(mgr.operate(leftNum, rightNum, operators.top()));
    operators.pop();
  }

  float res = evaluationStack.top();
  std::print("Result {}", res);

  // TODO:  Empty data structures
  return res;
}

/*
  ===============
  Public functions
  ================
*/

/**
 * Executes the specified expression.
 *
 * @param expression (`string`) The expression you want to evaluate.
 * @param debug (`bool`) If set to `true`, enables debugging outputs.
 */
float Evaluator::execute(std::string expression, bool debug) {
  this->expression = expression;
  this->debug = debug;

  readExpression();

  // Todo: RETURN the actual result.
  return 0;
}