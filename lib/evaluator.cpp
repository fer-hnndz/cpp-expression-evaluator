#include <iostream>
#include "operators.h"
#include <vector>
#include <stack>

/**
 * Parses the specified expression and returns the result.
 */
auto readExpression(std::string expr)
{
    int i = 0;
    OperatorsManager operatorsMgr;

    std::vector<float> operands;
    std::stack<char> operators;

    std::string currentToken = "";
    std::cout << "Length " << expr.length() << "\n";

    for (int i = 0; i < expr.length(); i++)
    {
        if (isdigit(expr.at(i)) || expr.at(i) == '.')
        {
            currentToken += expr.at(i);
            continue;
        }
        else
        {
            // TODO: Add try catch
            // There is another type of token, such as a variable or operator.
            if (!currentToken.empty())
            {
                operands.push_back(std::stof(currentToken));
                currentToken = "";
            }
        }

        if (operatorsMgr.isValidOperator(expr.at(i)))
            operators.push(expr.at(i));
    }

    // Agrega el último número si quedó pendiente
    if (!currentToken.empty())
    {
        operands.push_back(std::stof(currentToken));
    }

    // Imprimir el vector de números
    std::cout << "Operands: ";
    for (float num : operands)
    {
        std::cout << num << " ";
    }
    std::cout << "\n";

    // Imprimir la pila de operadores
    std::cout << "Operators: ";
    while (!operators.empty())
    {
        std::cout << operators.top() << " ";
        operators.pop();
    }
    std::cout << "\n";

    return 0;
}
