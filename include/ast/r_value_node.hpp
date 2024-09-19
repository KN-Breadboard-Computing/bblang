#ifndef AST_R_VALUE_NODE_HPP
#define AST_R_VALUE_NODE_HPP

#include "ast_node.hpp"
#include "ast_visitor.hpp"
#include "arithmetic_constant_node.hpp"
#include "logic_constant_node.hpp"

namespace ast {
class RValueNode : public AstNode {
 public:
  RValueNode() = default;

  RValueNode(size_t line_number, AstNode* value) : AstNode{Kind::R_VALUE, line_number}, value_{value} {}

  RValueNode(size_t line_number, ArithmeticConstantNode* arithmetic_constant)
      : AstNode{Kind::R_VALUE, line_number}, value_{arithmetic_constant} {}

  RValueNode(size_t line_number, LogicConstantNode* logic_constant)
      : AstNode{Kind::R_VALUE, line_number}, value_{logic_constant} {}

  RValueNode(const RValueNode&) = delete;
  RValueNode(RValueNode&&) = default;

  RValueNode& operator=(const RValueNode&) = delete;
  RValueNode& operator=(RValueNode&&) = default;

  ~RValueNode() = default;

  static bool classof(const RValueNode* node) { return node->getKind() == ast::Kind::R_VALUE; }

  const std::unique_ptr<AstNode>& getValue() const { return value_; }

  void accept(class AstVisitor* visitor) const override { visitor->visit(this); }
  [[nodiscard]] virtual std::unique_ptr<AstNode> clone() const override;
  void print(std::ostream& out, int tab) const override;

 private:
  std::unique_ptr<AstNode> value_;
};
}  // namespace ast

#endif  // AST_R_VALUE_NODE_HPP
