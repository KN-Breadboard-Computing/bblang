#ifndef SEMANTIC_CHECK_HPP
#define SEMANTIC_CHECK_HPP

#include "../ast/ast_visitor.hpp"

namespace semantic_check {
class SemanticCheck : public ast::AstVisitor {
 public:
  SemanticCheck() = default;

  SemanticCheck(const SemanticCheck&) = default;
  SemanticCheck(SemanticCheck&&) = default;

  SemanticCheck& operator=(const SemanticCheck&) = default;
  SemanticCheck& operator=(SemanticCheck&&) = default;

  ~SemanticCheck() = default;

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

  bool getValidity() const { return isValid_; }

 private:
  bool isValid_{true};
};
}  // namespace semantic_check

#endif  // SEMANTIC_CHECK_HPP
