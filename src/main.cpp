#include <bits/stdc++.h>

#include <iostream>
#include <print>
#include <string>

#include "evaluator.h"
#include "tags.h"

std::string parseInputs(int argc, char *argv[], bool &debug);

int main(int argc, char *argv[]) {
  bool debug = false;

  std::stack<char> operatorStack;
  Evaluator ev;

  const std::string expr = parseInputs(argc, argv, debug);

  if (expr.length() == 0)
    return 0;

  auto a = ev.execute(expr, debug);
  return 0;
}

/**
 * Parses the CLI inputs and returns the expression the user inputted.
 * Prints the help menu if --help tag is specified.
 */
std::string parseInputs(int argc, char *argv[], bool &debug) {
  // Check if user has enough arguments
  if (argc < 2) {
    std::print(HELP_MESSAGE);
    std::print("\n");
    return "";
  }

  const std::string expr = argv[1];

  for (int i = 1; i < argc; i++) {
    if (std::string(argv[i]) == HELP_TAG) {
      std::cout << HELP_MESSAGE;
      return "";
    }

    if (std::string(argv[i]) == "--debug")
      debug = true;
  }

  return expr;
}
