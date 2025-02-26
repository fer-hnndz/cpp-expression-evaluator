#include <iostream>
#include <vector>
#include <stack>
#include <print>

#include "operators.h"
#include "debug_logs.h"

std::expected<float, std::string> evaluateExpression(std::vector<std::string> operands, std::stack<char> operators)
{

    std::stack<float> evaluationStack;
    OperatorsManager operatorsMgr;

    // Add numbers to the evaluation stack until an operator in the operands is found.

    for (int i = 0; i < operands.size(); i++)
    {
        std::string currentOperand = operands.at(i);

        if (!operatorsMgr.isValidOperator(currentOperand.at(0)))
        {
            evaluationStack.push(std::stof(currentOperand));
            continue;
        }

        float rightNum = evaluationStack.top();
        evaluationStack.pop();
        float leftNum = evaluationStack.top();
        evaluationStack.pop();

        float result = operatorsMgr.operate(leftNum, rightNum, currentOperand.at(0));
        evaluationStack.push(result);
    }

    // Finished iterating over the operands (so we process any operator located there)
    // Process now the operator stack
    while (!operators.empty())
    {
        float rightNum = evaluationStack.top();
        evaluationStack.pop();
        float leftNum = evaluationStack.top();
        evaluationStack.pop();

        evaluationStack.push(operatorsMgr.operate(leftNum, rightNum, operators.top()));
        operators.pop();
    }

    std::print("Result {}", evaluationStack.top());
    return evaluationStack.top();
}

/**
 * Parses the specified expression and returns the result.
 *
 * @param expr The mathematical expression to parse.
 * @param debug If true, enables debug messages for parsing.
 *
 * @return std::expected<float, std::string>
 * - **Success (`float`)**: The computed result of the expression.
 * - **Error (`std::string`)**: An error message describing the failure reason.
 *
 * @retval float The computed result if the expression is valid.
 * @retval std::string An error message if parsing fails.
 */
std::expected<float, std::string> readExpression(std::string expr, bool debug)
{
    int i = 0;
    OperatorsManager operatorsMgr;

    std::vector<std::string> operands;
    std::stack<char> operators;

    std::string storedOperand = "";
    std::print("Length {}\n", expr.length());

    // Iterate over the expression
    for (int i = 0; i < expr.length(); i++)
    {
        char currentToken = expr.at(i);

        if (isdigit(currentToken) || currentToken == '.')
        {
            storedOperand += currentToken;
            continue;
        }
        else
        {
            // TODO: Add try catch
            // There is another type of token, such as a variable or operator.
            if (!storedOperand.empty())
            {
                operands.push_back(storedOperand);
                storedOperand = "";
            }
        }

        if (operatorsMgr.isValidOperator(currentToken))
        {
            // std::print("Before\n");
            // printPostfixExpression(operators, operands);

            // If the operators stack is empty, we can push the current operator.
            if (operators.empty())
            {
                operators.push(currentToken);
                continue;
            }

            // If the operator is a `)`, remove all operators until the `(` is found.
            if (currentToken == ')')
            {
                if (operators.empty())
                    return std::unexpected("Invalid expression: No opening parenthesis found.");

                while (operators.top() != '(')
                {
                    // Push the operator to the operands list. So we process it in a postfix manner.
                    operands.push_back(std::string(1, operators.top()));
                    operators.pop();
                }

                operators.pop(); // Remove the `(`.
                // operators.pop(); // Remove also the operator after the `(`.
                continue;
            }

            int currentPrecedence = operatorsMgr.getOperatorPrecedence(currentToken);
            int stackPrecedence = operatorsMgr.getOperatorPrecedence(operators.top());

            if (currentPrecedence >= stackPrecedence && stackPrecedence > 0)
            {

                char lastOperator = operators.top();
                operators.pop();

                // This is so we keep operate with this operator, but after the current operator has been operated with.
                // (not the best explanation, ik.)

                operands.push_back(std::string(1, lastOperator));
                operators.push(currentToken);
            }
            else
                operators.push(currentToken);

            // std::print("After\n");

            // printPostfixExpression(operators, operands);
        }
    }

    // Add last number if it exists
    if (!storedOperand.empty())
        operands.push_back(storedOperand);

    // Print operands list and operators stack if running in debug mode.
    if (debug)
    {
        printPostfixExpression(operators, operands);
    }

    std::print("Evaluating...");
    auto r = evaluateExpression(operands, operators);

    // print("Res {}", r);

    return 0;
}