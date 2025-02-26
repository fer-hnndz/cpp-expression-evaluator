#ifndef H_OPERATORS

#include <map>

class OperatorsManager
{
private:
    std::map<char, short> operatorsPrecedence;

public:
    OperatorsManager()
    {
        operatorsPrecedence['('] = 0;
        operatorsPrecedence[')'] = 0;
        operatorsPrecedence['^'] = 0;
        operatorsPrecedence['*'] = 2;
        operatorsPrecedence['/'] = 2;
        operatorsPrecedence['%'] = 2;
        operatorsPrecedence['+'] = 3;
        operatorsPrecedence['-'] = 3;
    }

    short getOperatorPrecedence(char op)
    {
        return operatorsPrecedence[op];
    }

    bool isValidOperator(char op)
    {
        return operatorsPrecedence.find(op) != operatorsPrecedence.end();
    }
};

#endif;