#ifndef H_OPERATORS
#define H_OPERATORS

#include <expected>
#include <map>
#include <math.h>

class OperatorsManager {
private:
  std::map<char, short> operatorsPrecedence;

public:
  OperatorsManager() {
    operatorsPrecedence['('] = 0;
    operatorsPrecedence[')'] = 0;
    operatorsPrecedence['^'] = 0;
    operatorsPrecedence['*'] = 2;
    operatorsPrecedence['/'] = 2;
    operatorsPrecedence['%'] = 2;
    operatorsPrecedence['+'] = 3;
    operatorsPrecedence['-'] = 3;
  }

  short getOperatorPrecedence(char op) {
    if (isValidOperator(op))
      return operatorsPrecedence[op];
    return -1;
  }

  bool isValidOperator(char op) {
    return operatorsPrecedence.find(op) != operatorsPrecedence.end();
  }

  float operate(float left, float right, char op) {
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
      return powf(left, right);
    }

    // throw new error here
  }
};

#endif