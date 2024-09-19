#ifndef AST_REAL_NODE_HPP
#define AST_REAL_NODE_HPP

#include "ast_node.hpp"

namespace ast {
class RealNode : public AstNode {
 public:
  RealNode() = default;

  RealNode(double value) : value_{value} {}

  RealNode(const RealNode&) = delete;
  RealNode(RealNode&&) = default;

  RealNode& operator=(const RealNode&) = delete;
  RealNode& operator=(RealNode&&) = default;

  ~RealNode() = default;

  double getValue() const { return value_; }

  void accept(class AstVisitor* visitor) const override { visitor->visit(this); }

  [[nodiscard]] virtual std::unique_ptr<AstNode> clone() const override { return std::make_unique<RealNode>(value_); }

  void print(std::ostream& out, int tab) const override {
    out << std::string(tab, ' ') << "RealNode(" << value_ << ")" << std::endl;
  }

 private:
  double value_;
};
}  // namespace ast

#endif  // AST_REAL_NODE_HPP