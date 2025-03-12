#include <bits/stdc++.h>

#include <iostream>
#include <print>
#include <string>

#include "evaluator.h"
#include "tags.h"

std::expected<std::string, float> parseInputs(int argc, char *argv[], bool &debug, std::string &configPath);

int main(int argc, char *argv[]) {
  bool debug = false;

  std::string configPath = "";
  const std::expected<std::string, float> parseResult = parseInputs(argc, argv, debug, configPath);

  if (!parseResult.has_value())
    if (parseResult.error() == -1) {
      std::print("Please make sure to use all options correctly.");
      std::print(HELP_MESSAGE);
      std::print("\n");

      return -1;
    }

  const std::string expr = parseResult.value();

  ConfigParser config;
  Evaluator *ev = nullptr;

  if (configPath.empty())
    config.loadConfig();
  else
    config.loadConfig(configPath);

  ev = new Evaluator(&config);
  double a = ev->execute(expr, debug);

  std::print("Result: {}\n", a);

  delete ev;
  return 0;
}

/**
 * Parses the CLI inputs and returns the expression the user inputted.
 * Prints the help menu if --help tag is specified.
 */
std::expected<std::string, float> parseInputs(int argc, char *argv[], bool &debug, std::string &configPath) {
  // Check if user has enough arguments
  if (argc < 2) {
    std::print(HELP_MESSAGE);
    std::print("\n");
    return std::unexpected(-1);
  }

  const std::string expr = argv[1];

  for (int i = 1; i < argc; i++) {
    if (std::string(argv[i]) == HELP_TAG) {
      std::cout << HELP_MESSAGE;
      return std::unexpected(0);
    }

    if (std::string(argv[i]) == "--debug")
      debug = true;

    if (std::string(argv[i]) == "--help") {
      std::cout << HELP_MESSAGE;
      return std::unexpected(0);
    }

    if (std::string(argv[i]) == "--config") {
      if (i == argc - 1) {
        return std::unexpected(-1);
      }

      configPath = argv[i + 1];
      continue;
    }
  }

  return expr;
}
