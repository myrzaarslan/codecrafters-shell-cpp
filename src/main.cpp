#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <filesystem>

namespace fs = std::filesystem;

int main() {
  std::cout << std::unitbuf;
  std::cerr << std::unitbuf;

  std::vector<std::string> commands = {"exit", "echo", "type"};

  while (true) {
    std::string input;
    std::cout << "$ ";
    std::getline(std::cin, input);

    std::istringstream iss(input);
    std::string command;
    iss >> command;

    if (command == "exit") {
      std::string code;
      iss >> code;
      if (code == "0") break;
    } else if (command == "echo") {
      std::string word;
      bool first = true;
      while (iss >> word) {
        if (!first) std::cout << " ";
        std::cout << word;
        first = false;
      }
      std::cout << std::endl;
    } else if (command == "type") {
      std::string word;
      iss >> word;

      if (std::find(commands.begin(), commands.end(), word) != commands.end()) {
          std::cout << word << " is a shell builtin" << std::endl;
      } else {
          const char* path_env = std::getenv("PATH");
          if (path_env) {
              std::string path_str = path_env;
              std::istringstream path_stream(path_str);
              std::string dir;
              bool found = false;

              while (std::getline(path_stream, dir, ':')) {
                  fs::path full_path = fs::path(dir) / word;
                  if (fs::exists(full_path) && fs::is_regular_file(full_path) &&
                      (fs::status(full_path).permissions() & fs::perms::owner_exec) != fs::perms::none) {
                      std::cout << word << " is " << full_path << std::endl;
                      found = true;
                      break;
                  }
              }

              if (!found) {
                  std::cout << word << ": not found" << std::endl;
              }
          } else {
              std::cout << word << ": not found" << std::endl;
          }
      }
    } else {
      std::cout << input << ": command not found" << std::endl;
    }
  }

  return 0;
}

