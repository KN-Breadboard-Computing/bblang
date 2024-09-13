#include <iostream>

#include "src/parser/calc_parser.hpp"
#include "calculator.hpp"

std::unique_ptr<ast::ProgramNode> parse(const char* file_path);

int main(int argc, char* argv[]) {
  constexpr int expectedArgumentsNumber{2};
  if (argc != expectedArgumentsNumber) {
    std::cerr << "Usage: " << argv[0] << " <input-file>" << std::endl;
    return 1;
  }

  std::unique_ptr<ast::ProgramNode> programTree = parse(argv[1]);
  std::cout << *programTree << std::endl;

  Calculator calculator;
  std::cout << "Calculating result = " << calculator.calc(programTree.get()) << std::endl;

  return 0;
}
