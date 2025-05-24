#include <iostream>
#include <string>
#include <sstream>

int main() {
  std::cout << std::unitbuf;
  std::cerr << std::unitbuf;

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
    } else {
      std::cout << input << ": command not found" << std::endl;
    }
  }

  return 0;
}

