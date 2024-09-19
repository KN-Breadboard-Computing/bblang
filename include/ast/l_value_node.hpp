#ifndef AST_L_VALUE_NODE_HPP
#define AST_L_VALUE_NODE_HPP

#include "ast_node.hpp"
#include "ast_visitor.hpp"
#include "identifier_node.hpp"

namespace ast {
class LValueNode : public AstNode {
 public:
  LValueNode() = default;

  LValueNode(size_t line_number, IdentifierNode* identifier) : AstNode{Kind::L_VALUE, line_number}, identifier_{identifier} {}

  LValueNode(const LValueNode&) = delete;
  LValueNode(LValueNode&&) = default;

  LValueNode& operator=(const LValueNode&) = delete;
  LValueNode& operator=(LValueNode&&) = default;

  ~LValueNode() = default;

  static bool classof(const LValueNode* node) { return node->getKind() == ast::Kind::L_VALUE; }

  const std::unique_ptr<IdentifierNode>& getIdentifier() const { return identifier_; }

  void accept(class AstVisitor* visitor) const override { visitor->visit(this); }
  [[nodiscard]] virtual std::unique_ptr<AstNode> clone() const override;
  void print(std::ostream& out, int tab) const override;

 private:
  std::unique_ptr<IdentifierNode> identifier_;
};
}  // namespace ast

#endif  // AST_L_VALUE_NODE_HPP
