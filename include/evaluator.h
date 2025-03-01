#ifndef EVALUATOR_H
#define EVALUATOR_H

#include <expected>
#include <stack>
#include <string>
#include <vector>

std::expected<float, std::string> readExpression(std::string expr, bool debug);
std::expected<float, std::string>
evaluateExpression(std::vector<std::string> terms, std::stack<char> operators);

#endif