#ifndef H_OPERATORS
#define H_OPERATORS

#include <expected>
#include <map>
#include <math.h>

class OperatorsManager {
private:
  std::map<char, short> operatorsPrecedence;

public:
  OperatorsManager();

  short getOperatorPrecedence(char op);
  bool isValidOperator(char op);

  float operate(float left, float right, char op);
};

#endif