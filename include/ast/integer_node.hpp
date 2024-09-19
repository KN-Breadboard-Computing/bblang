#ifndef AST_INTEGER_NODE_HPP
#define AST_INTEGER_NODE_HPP

#include "ast_node.hpp"

namespace ast {
class IntegerNode : public AstNode {
 public:
  IntegerNode() = default;

  IntegerNode(int value) : value_{value} {}

  IntegerNode(const IntegerNode&) = delete;
  IntegerNode(IntegerNode&&) = default;

  IntegerNode& operator=(const IntegerNode&) = delete;
  IntegerNode& operator=(IntegerNode&&) = default;

  ~IntegerNode() = default;

  int getValue() const { return value_; }

  void accept(class AstVisitor* visitor) const override { visitor->visit(this); }

  [[nodiscard]] virtual std::unique_ptr<AstNode> clone() const override { return std::make_unique<IntegerNode>(value_); }

  void print(std::ostream& out, int tab) const override {
    out << std::string(tab, ' ') << "IntegerNode(" << value_ << ")" << std::endl;
  }

 private:
  int value_;
};
}  // namespace ast

#endif  // AST_INTEGER_NODE_HPP
