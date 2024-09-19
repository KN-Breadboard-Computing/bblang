#ifndef AST_LOGIC_CONSTANT_NODE_HPP
#define AST_LOGIC_CONSTANT_NODE_HPP

#include "ast_node.hpp"
#include "ast_visitor.hpp"

namespace ast {
class LogicConstantNode : public AstNode {
 public:
  enum class LogicConstantNodeOperation { UNDEF, FALSE, TRUE };

  LogicConstantNode() = default;

  LogicConstantNode(size_t line_number, LogicConstantNodeOperation operation)
      : AstNode{Kind::LOGIC_CONSTANT, line_number}, operation_{operation} {}

  LogicConstantNode(const LogicConstantNode&) = delete;
  LogicConstantNode(LogicConstantNode&&) = default;

  LogicConstantNode& operator=(const LogicConstantNode&) = delete;
  LogicConstantNode& operator=(LogicConstantNode&&) = default;

  ~LogicConstantNode() = default;

  static bool classof(const LogicConstantNode* node) { return node->getKind() == ast::Kind::LOGIC_CONSTANT; }

  LogicConstantNodeOperation getOperation() const { return operation_; }

  void accept(class AstVisitor* visitor) const override { visitor->visit(this); }
  [[nodiscard]] virtual std::unique_ptr<AstNode> clone() const override;
  void print(std::ostream& out, int tab) const override;

 private:
  LogicConstantNodeOperation operation_;
};
}  // namespace ast

#endif  // AST_LOGIC_CONSTANT_NODE_HPP
