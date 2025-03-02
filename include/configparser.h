#ifndef CONFIG_PARSER_H
#define CONFIG_PARSER_H

#define CONFIG_FILENAME "config.cee"

#include <map>
#include <string>

class ConfigParser {
private:
  std::map<std::string, float> constants;
  void parse(std::string path);

  std::string stripString(std::string str);

public:
  ConfigParser();
  void loadConfig(std::string path);
  void loadConfig();
  float *get(std::string key);
};

#endif