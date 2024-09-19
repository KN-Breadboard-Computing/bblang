#include "../../include/code-gen/code_gen.hpp"

#include <llvm/Support/FileSystem.h>
#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/Type.h"
#include "llvm/IR/Verifier.h"

namespace code_gen {
void CodeGen::visit(const ast::ArithmeticConstantNode* /*node*/) {}
void CodeGen::visit(const ast::ArithmeticExprLvl1Node* /*node*/) {}
void CodeGen::visit(const ast::ArithmeticExprLvl2Node* /*node*/) {}
void CodeGen::visit(const ast::ArithmeticExprLvl3Node* /*node*/) {}
void CodeGen::visit(const ast::ArithmeticExprLvl4Node* /*node*/) {}
void CodeGen::visit(const ast::ArithmeticExprLvl5Node* /*node*/) {}
void CodeGen::visit(const ast::ArithmeticExpressionNode* /*node*/) {}
void CodeGen::visit(const ast::ArithmeticExpressionsComparisonNode* /*node*/) {}
void CodeGen::visit(const ast::ArithmeticTermNode* /*node*/) {}
void CodeGen::visit(const ast::IdentifierNode* /*node*/) {}
void CodeGen::visit(const ast::IntegerNode* /*node*/) {}
void CodeGen::visit(const ast::LValueNode* /*node*/) {}
void CodeGen::visit(const ast::LogicConstantNode* /*node*/) {}
void CodeGen::visit(const ast::LogicExprLvl1Node* /*node*/) {}
void CodeGen::visit(const ast::LogicExprLvl2Node* /*node*/) {}
void CodeGen::visit(const ast::LogicExpressionNode* /*node*/) {}
void CodeGen::visit(const ast::LogicTermNode* /*node*/) {}
void CodeGen::visit(const ast::ProgramNode* /*node*/) {}
void CodeGen::visit(const ast::RValueNode* /*node*/) {}
void CodeGen::visit(const ast::RealNode* /*node*/) {}

void CodeGen::saveLLVMIr(const std::string output_file_name) const {
  std::error_code error;
  llvm::raw_fd_ostream output_file(output_file_name, error, llvm::sys::fs::OF_Text);

  if (error) {
    llvm::errs() << "Error opening file: " << error.message() << "\n";
    return;
  }

  context_.getModule()->print(output_file, nullptr);

  output_file.close();
}
}  // namespace code_gen
