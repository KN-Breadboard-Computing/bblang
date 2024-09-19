#include <iostream>

#include "../include/code-gen/code_gen.hpp"
#include "../include/semantic-check/semantic_check.hpp"
#include "parser/bblang_parser.hpp"

std::unique_ptr<ast::ProgramNode> parse(const char* file_path);

int main(int argc, char* argv[]) {
  constexpr int expectedArgumentsNumber{3};
  if (argc != expectedArgumentsNumber) {
    std::cerr << "Usage: " << argv[0] << " <input_ast-file> <output-asm-file>" << std::endl;
    return 1;
  }

  std::unique_ptr<ast::ProgramNode> programTree = parse(argv[1]);

  std::cout << *programTree << std::endl;

  semantic_check::SemanticCheck semanticCheck;
  semanticCheck.visit(programTree.get());
  if (!semanticCheck.getValidity()) {
    std::cout << "Semantic check failed" << std::endl;
    return 1;
  }

  code_gen::CodeGen codeGen;
  codeGen.visit(programTree.get());
  codeGen.saveLLVMIr(argv[2]);
  return 0;
}
