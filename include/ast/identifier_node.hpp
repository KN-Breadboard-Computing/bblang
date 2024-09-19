#ifndef AST_IDENTIFIER_NODE_HPP
#define AST_IDENTIFIER_NODE_HPP

#include "ast_node.hpp"

namespace ast {
class IdentifierNode : public AstNode {
 public:
  IdentifierNode() = default;

  IdentifierNode(const std::string& identifier) : identifier_{identifier} {}

  IdentifierNode(const IdentifierNode&) = delete;
  IdentifierNode(IdentifierNode&&) = default;

  IdentifierNode& operator=(const IdentifierNode&) = delete;
  IdentifierNode& operator=(IdentifierNode&&) = default;

  ~IdentifierNode() = default;

  const std::string& getIdentifier() const { return identifier_; }

  void accept(class AstVisitor* visitor) const override { visitor->visit(this); }

  [[nodiscard]] virtual std::unique_ptr<AstNode> clone() const override { return std::make_unique<IdentifierNode>(identifier_); }

  void print(std::ostream& out, int tab) const override {
    out << std::string(tab, ' ') << "IdentifierNode(" << identifier_ << ")" << std::endl;
  }

 private:
  std::string identifier_;
};
}  // namespace ast

#endif  // AST_IDENTIFIER_NODE_HPP