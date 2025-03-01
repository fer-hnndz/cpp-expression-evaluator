#ifndef H_DEBUG_LOGS
#define H_DEBUG_LOGS

#include <print>
#include <stack>
#include <vector>

void printStacks(std::stack<char> operators,
                 const std::vector<std::string> operands);

void printPostfixExpression(std::stack<char> operators,
                            const std::vector<std::string> operands);

#endif