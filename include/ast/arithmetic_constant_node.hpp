#ifndef AST_ARITHMETIC_CONSTANT_NODE_HPP
#define AST_ARITHMETIC_CONSTANT_NODE_HPP

#include "ast_node.hpp"
#include "ast_visitor.hpp"
#include "integer_node.hpp"
#include "real_node.hpp"

namespace ast {
class ArithmeticConstantNode : public AstNode {
 public:
  ArithmeticConstantNode() = default;

  ArithmeticConstantNode(size_t line_number, AstNode* number)
      : AstNode{Kind::ARITHMETIC_CONSTANT, line_number}, number_{number} {}

  ArithmeticConstantNode(size_t line_number, IntegerNode* integer)
      : AstNode{Kind::ARITHMETIC_CONSTANT, line_number}, number_{integer} {}

  ArithmeticConstantNode(size_t line_number, RealNode* real) : AstNode{Kind::ARITHMETIC_CONSTANT, line_number}, number_{real} {}

  ArithmeticConstantNode(const ArithmeticConstantNode&) = delete;
  ArithmeticConstantNode(ArithmeticConstantNode&&) = default;

  ArithmeticConstantNode& operator=(const ArithmeticConstantNode&) = delete;
  ArithmeticConstantNode& operator=(ArithmeticConstantNode&&) = default;

  ~ArithmeticConstantNode() = default;

  static bool classof(const ArithmeticConstantNode* node) { return node->getKind() == ast::Kind::ARITHMETIC_CONSTANT; }

  const std::unique_ptr<AstNode>& getNumber() const { return number_; }

  void accept(class AstVisitor* visitor) const override { visitor->visit(this); }
  [[nodiscard]] virtual std::unique_ptr<AstNode> clone() const override;
  void print(std::ostream& out, int tab) const override;

 private:
  std::unique_ptr<AstNode> number_;
};
}  // namespace ast

#endif  // AST_ARITHMETIC_CONSTANT_NODE_HPP
