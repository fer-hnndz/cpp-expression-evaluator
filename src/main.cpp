#include <iostream>
#include <string>
#include <bits/stdc++.h>

#include "tags.h"
#include "evaluator.cpp"

std::string parseInputs(int argc, char *argv[], bool &debug);

int main(int argc, char *argv[])
{

    std::stack<char> operatorStack;

    bool debug = false;
    const std::string expr = parseInputs(argc, argv, debug);

    if (sizeof expr == 0)
        return 0;

    int a = readExpression(expr);
    return 0;
}

/**
 * Parses the CLI inputs and returns the expression the user inputted.
 * Prints the help menu if --help tag is specified.
 */
std::string parseInputs(int argc, char *argv[], bool &debug)
{

    // Check if user has enough arguments
    if (argc < 2)
    {
        std::cout << HELP_MESSAGE << "\n";
        return "";
    }

    const std::string expr = argv[1];

    for (int i = 1; i < argc; i++)
    {
        if (std::string(argv[i]) == HELP_TAG)
        {
            std::cout << HELP_MESSAGE;
            return "";
        }

        if (std::string(argv[i]) == "--debug")
            debug = true;
    }

    return expr;
}
