#ifndef CODE_GEN_HPP
#define CODE_GEN_HPP

#include <list>
#include <ostream>
#include <stack>

#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/NoFolder.h>

#include "../ast/ast_visitor.hpp"
#include "context.hpp"

namespace code_gen {
class CodeGen : public ast::AstVisitor {
 public:
  CodeGen() = default;

  CodeGen(const CodeGen&) = delete;
  CodeGen(CodeGen&&) = delete;

  CodeGen& operator=(const CodeGen&) = delete;
  CodeGen& operator=(CodeGen&&) = delete;

  ~CodeGen() = default;

  void visit(const ast::ArithmeticConstantNode* node) override;
  void visit(const ast::ArithmeticExprLvl1Node* node) override;
  void visit(const ast::ArithmeticExprLvl2Node* node) override;
  void visit(const ast::ArithmeticExprLvl3Node* node) override;
  void visit(const ast::ArithmeticExprLvl4Node* node) override;
  void visit(const ast::ArithmeticExprLvl5Node* node) override;
  void visit(const ast::ArithmeticExpressionNode* node) override;
  void visit(const ast::ArithmeticExpressionsComparisonNode* node) override;
  void visit(const ast::ArithmeticTermNode* node) override;
  void visit(const ast::IdentifierNode* node) override;
  void visit(const ast::IntegerNode* node) override;
  void visit(const ast::LValueNode* node) override;
  void visit(const ast::LogicConstantNode* node) override;
  void visit(const ast::LogicExprLvl1Node* node) override;
  void visit(const ast::LogicExprLvl2Node* node) override;
  void visit(const ast::LogicExpressionNode*) override;
  void visit(const ast::LogicTermNode* node) override;
  void visit(const ast::ProgramNode* node) override;
  void visit(const ast::RValueNode* node) override;
  void visit(const ast::RealNode* node) override;

  void saveLLVMIr(const std::string output_file_name) const;

 private:
  Context context_;
  std::stack<llvm::Value*> stack_;
  llvm::Function* mainFunction_{nullptr};
  llvm::IRBuilder<llvm::NoFolder> builder_{context_.getGlobalContext()};
};
}  // namespace code_gen

#endif  // CODE_GEN_HPP
