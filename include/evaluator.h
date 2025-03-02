#ifndef EVALUATOR_H
#define EVALUATOR_H

#include "configparser.h"
#include "operators.h"
#include <expected>
#include <stack>
#include <string>
#include <vector>

class Evaluator {
private:
  OperatorsManager mgr;
  ConfigParser *constants;

  std::string termBuffer;
  std::vector<std::string> terms;
  std::stack<char> operators;
  std::string expression;

  bool debug = false;

  // Entry point to the parsing and debug printing
  std::expected<float, std::string> readExpression();

  // Asks for variable's values and executes the operations.
  std::expected<float, std::string> evaluateExpression();

  // Parsing functions
  void iterateTokens();
  void parenthesesToTerm();
  void pushTerm(std::string &termBuffer);
  void handleOperator(char op);

  // Debug prints.

  void printStacks(std::stack<char> operators, const std::vector<std::string> terms);
  void printPostfixExpression(std::stack<char> operators, const std::vector<std::string> terms);

public:
  Evaluator();
  Evaluator(ConfigParser *constants);
  ~Evaluator();

  float execute(std::string expression, bool debug);
};
#endif