#include "debug_logs.h"

void printStacks(std::stack<char> operators,
                 const std::vector<std::string> operands) {
  std::print("Operators: ");

  while (!operators.empty()) {
    std::print("{}, ", operators.top());
    operators.pop();
  }

  std::print("\nOperands: ");
  for (std::string op : operands) {
    std::print("{}, ", op);
  }
  std::print("\n");
}
void printPostfixExpression(std::stack<char> operators,
                            const std::vector<std::string> operands) {
  printStacks(operators, operands);

  std::print("Postfix Syntax: ");
  for (std::string operand : operands) {
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