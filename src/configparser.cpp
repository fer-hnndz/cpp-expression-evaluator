#include "configparser.h"
#include <filesystem>
#include <fstream>
#include <print>
#include <regex>

ConfigParser::ConfigParser() {}

std::string ConfigParser::stripString(std::string str) {
  size_t start = 0;
  while (start < str.length() && std::isspace(str[start])) {
    start++;
  }

  size_t end = str.length();
  while (end > start && std::isspace(str[end - 1])) {
    end--;
  }

  return str.substr(start, end - start);
}

void ConfigParser::parse(std::string path) {
  std::ifstream file(path);

  if (!file.is_open())
    throw std::runtime_error("Cannot open config file: " + path);

  std::string line;
  std::regex keyRegex(R"(^[a-zA-Z][a-zA-Z0-9]*$)");

  while (std::getline(file, line)) {

    // Allow comments
    if (line.at(0) == '#')
      continue;

    std::string key = stripString(line.substr(0, line.find('=')));
    std::string value = stripString(line.substr(line.find('=') + 1));

    if (!std::regex_match(key, keyRegex))
      throw std::format_error("Invalid constant in config file: " + key);

    if (constants.find(key) != constants.end())
      throw std::format_error("Duplicate constant in config file: " + key);

    try {
      std::print("Attempting to set constant {} to {}\n", key, value);
      this->constants[key] = std::stof(value);

    } catch (std::exception &e) {
      throw std::format_error("Invalid value " + value + " for constant " + key + "in config file");
    }
  }

  file.close();
}

/**
 * Attempt to find and load a config file in the current working directory.
 */
void ConfigParser::loadConfig() {
  std::filesystem::path configPath = std::filesystem::current_path() / "config.cee";

  std::print("Looking for config file at: {}\n", configPath.string());

  if (!std::filesystem::exists(configPath))
    return;

  parse(configPath.string());
}

/**
 * Load a config file from a given path.
 *
 * @param path The path to the config file.
 */
void ConfigParser::loadConfig(std::string path) { parse(path); }

/**
 * Get the value of a constant from the config file.
 *
 * @param key The key of the constant.
 * @return A pointer to the value of the constant. `nullptr` if the constant is not found. Delete the pointer after use.
 */
float *ConfigParser::get(std::string key) {
  if (constants.find(key) == constants.end())
    return nullptr;

  return &constants[key];
};