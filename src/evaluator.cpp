#include <iostream>
#include <print>
#include <stack>
#include <stdexcept>
#include <vector>

#include "debug_logs.h"
#include "evaluator.h"
#include "operators.h"

std::expected<float, std::string>
evaluateExpression(std::vector<std::string> terms, std::stack<char> operators) {
  std::stack<float> evaluationStack;
  OperatorsManager operatorsMgr;

  // Add numbers to the evaluation stack until an operator in the operands is
  // found.

  for (int i = 0; i < terms.size(); i++) {
    std::string currentTerm = terms.at(i);

    bool isTerm = !operatorsMgr.isValidOperator(currentTerm.at(0)) &&
                  (isalpha(currentTerm.at(0)) || isdigit(currentTerm.at(0)));

    if (isTerm) {
      if (isdigit(currentTerm.at(0))) {
        evaluationStack.push(std::stof(currentTerm));
        continue;
      }

      // Ask for the value of the variable.
      std::print("Enter the value of the variable {}: ", currentTerm);
      float *value = new float;
      std::cin >> *value;

      evaluationStack.push(*value);
      delete value;
      continue;
    }

    // Here we have detected an operation in the terms stack.
    // Possibly from a parentheses term.

    float rightNum = evaluationStack.top();
    evaluationStack.pop();
    float leftNum = evaluationStack.top();
    evaluationStack.pop();

    float result = operatorsMgr.operate(leftNum, rightNum, currentTerm.at(0));
    evaluationStack.push(result);
  }

  // Finished iterating over the operands (so we process any operator located
  // there) Process now the operator stack
  while (!operators.empty()) {
    float rightNum = evaluationStack.top();
    evaluationStack.pop();
    float leftNum = evaluationStack.top();
    evaluationStack.pop();

    evaluationStack.push(
        operatorsMgr.operate(leftNum, rightNum, operators.top()));
    operators.pop();
  }

  std::print("Result {}", evaluationStack.top());
  return evaluationStack.top();
}

/**
 * Transforms the operators between parentheses to terms into the terms vector.
 *
 * @param operators The operators stack.
 * @param terms The terms vector.
 *
 * @throws std::invalid_argument If no opening parenthesis is found.
 */
void parenthesesToTerm(std::stack<char> &operators,
                       std::vector<std::string> &terms) {
  if (operators.empty())
    throw std::invalid_argument(
        "Invalid expression: No opening parenthesis found.");

  while (operators.top() != '(') {
    // Push all the operators to the terms list.
    terms.push_back(std::string(1, operators.top()));
    operators.pop();
  }

  operators.pop(); // Remove the `(`.
}

/**
 * Parses the specified expression and returns the result.
 *
 * @param expr The mathematical expression to parse.
 * @param debug If true, enables debug messages for parsing.
 *
 * @return std::expected<float, std::string>
 * - **Success (`float`)**: The computed result of the expression.
 * - **Error (`std::string`)**: An error message describing the failure
 * reason.
 *
 * @retval float The computed result if the expression is valid.
 * @retval std::string An error message if parsing fails.
 */
std::expected<float, std::string> readExpression(std::string expr, bool debug) {
  int i = 0;
  OperatorsManager operatorsMgr;

  std::vector<std::string> terms;
  std::stack<char> operators;

  std::string storedTerm = "";
  bool hasAlphanumeric = false;
  bool hasDotAlready = false;

  // Iterate over the expression
  for (int i = 0; i < expr.length(); i++) {
    char currentToken = expr.at(i);
    if (currentToken == ' ') {

      if (storedTerm.empty())
        continue;

      terms.push_back(storedTerm);
      storedTerm = "";
      continue;
    }

    bool isValidAlphanumeric = (isalnum(currentToken) || currentToken == '.') &&
                               !operatorsMgr.isValidOperator(currentToken);

    if (isValidAlphanumeric) {
      if (storedTerm.empty()) {
        // If the stored term is empty, then the current token should be a
        // number or a variable.
        storedTerm += currentToken;
        continue;
      }

      bool storedTermIsNumber = isdigit(storedTerm.at(0));

      if (!storedTermIsNumber)
        // tODO: raise an error if current token is a dot.

        // Stored term doesnt start with a number and current token is not an
        // operator. Then it should be a variable that accepts both numbers and
        // letters.

        // Just append the value
        storedTerm += currentToken;

      else { // Is a number

        // Don't accept two dots (.) in a number.
        if (hasDotAlready && currentToken == '.')
          throw std::invalid_argument(
              "Invalid number format: Multiple dots found in number.");

        // Only accept numbers if the stored term starts with a number.
        if (!isdigit(currentToken) && currentToken != '.')
          throw std::invalid_argument(
              "Invalid number format: Non-digit character found in number.");

        if (currentToken == '.')
          hasDotAlready = true;

        storedTerm += currentToken;
      }

      continue;
    }

    // Current character is an operator. Push the savedTerm to the terms list.
    if (!storedTerm.empty()) {
      terms.push_back(storedTerm);
      storedTerm = "";
      hasDotAlready = false;
    }

    if (!operatorsMgr.isValidOperator(currentToken))
      throw std::invalid_argument("Invalid operator found: " +
                                  std::string(1, currentToken));

    // If the operators stack is empty, or is a `(`, we can push the current
    // operator.
    if (operators.empty() || currentToken == '(') {
      operators.push(currentToken);
      continue;
    }

    // If the operator is a `)`, remove all operators until the `(` is
    // found. This is because, mathematically speaking an expression in a
    // parentheses is technically a term written in another way.
    // (2 + 1)x = 3x.

    if (currentToken == ')') {
      parenthesesToTerm(operators, terms);
      continue;
    }

    // Parse normally the operators.
    int currentPrecedence = operatorsMgr.getOperatorPrecedence(currentToken);
    int stackPrecedence = operatorsMgr.getOperatorPrecedence(operators.top());

    if (currentPrecedence >= stackPrecedence && stackPrecedence > 0) {
      char lastOperator = operators.top();
      operators.pop();

      // This is so we keep operate with this operator, but after the
      // current operator has been operated with. (not the best explanation,
      // ik.)

      terms.push_back(std::string(1, lastOperator));
      operators.push(currentToken);
    } else
      operators.push(currentToken);
  }

  // Push the last term if it exists.
  if (!storedTerm.empty())
    terms.push_back(storedTerm);

  // Print operands list and operators stack if running in debug mode.
  if (debug)
    printPostfixExpression(operators, terms);

  auto r = evaluateExpression(terms, operators);

  // print("Res {}", r);

  return 0;
}
