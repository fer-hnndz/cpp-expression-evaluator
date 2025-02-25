#include <iostream>
#include <string>

std::string parseInputs(int argc, char *argv[]);

int main(int argc, char *argv[])
{

    parseInputs(argc, argv);

    return 0;
}

/**
 * Parses the CLI inputs and returns the expression the user inputted.
 * Prints the help menu if --help tag is specified.
 */
std::string parseInputs(int argc, char *argvp[])
{
}