#ifndef AST_PROGRAM_NODE_HPP
#define AST_PROGRAM_NODE_HPP

#include "arithmetic_expression_node.hpp"
#include "ast_node.hpp"
#include "ast_visitor.hpp"
#include "logic_expression_node.hpp"

namespace ast {
class ProgramNode : public AstNode {
 public:
  ProgramNode() = default;

  ProgramNode(size_t line_number, AstNode* expression) : AstNode{Kind::PROGRAM, line_number}, expression_{expression} {}

  ProgramNode(size_t line_number, ArithmeticExpressionNode* arithmetic_expression)
      : AstNode{Kind::PROGRAM, line_number}, expression_{arithmetic_expression} {}

  ProgramNode(size_t line_number, LogicExpressionNode* logic_expression)
      : AstNode{Kind::PROGRAM, line_number}, expression_{logic_expression} {}

  ProgramNode(const ProgramNode&) = delete;
  ProgramNode(ProgramNode&&) = default;

  ProgramNode& operator=(const ProgramNode&) = delete;
  ProgramNode& operator=(ProgramNode&&) = default;

  ~ProgramNode() = default;

  static bool classof(const ProgramNode* node) { return node->getKind() == ast::Kind::PROGRAM; }

  const std::unique_ptr<AstNode>& getExpression() const { return expression_; }

  void accept(class AstVisitor* visitor) const override { visitor->visit(this); }
  [[nodiscard]] virtual std::unique_ptr<AstNode> clone() const override;
  void print(std::ostream& out, int tab) const override;

 private:
  std::unique_ptr<AstNode> expression_;
};
}  // namespace ast

#endif  // AST_PROGRAM_NODE_HPP
