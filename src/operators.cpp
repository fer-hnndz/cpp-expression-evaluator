#include "operators.h"
#include <stdexcept>

OperatorsManager::OperatorsManager() {
  operatorsPrecedence['('] = 0;
  operatorsPrecedence[')'] = 0;
  operatorsPrecedence['^'] = 0;
  operatorsPrecedence['*'] = 2;
  operatorsPrecedence['/'] = 2;
  operatorsPrecedence['%'] = 2;
  operatorsPrecedence['+'] = 3;
  operatorsPrecedence['-'] = 3;
}

short OperatorsManager::getOperatorPrecedence(char op) {
  return operatorsPrecedence[op];
}

bool OperatorsManager::isValidOperator(char op) {
  return operatorsPrecedence.find(op) != operatorsPrecedence.end();
}

float OperatorsManager::operate(float left, float right, char op) {
  switch (op) {
  case '+':
    return left + right;
  case '-':
    return left - right;
  case '*':
    return left * right;
  case '/':
    return left / right;
  case '%':
    return fmod(left, right);
  case '^':
    return pow(left, right);
  default:
    throw std::invalid_argument("Invalid operator found: " +
                                std::string(1, op));
  }
}