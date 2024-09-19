#ifndef AST_ARITHMETIC_TERM_NODE_HPP
#define AST_ARITHMETIC_TERM_NODE_HPP

#include "arithmetic_expression_node.hpp"
#include "ast_node.hpp"
#include "ast_visitor.hpp"
#include "l_value_node.hpp"
#include "r_value_node.hpp"

namespace ast {
class ArithmeticTermNode : public AstNode {
 public:
  enum class ArithmeticTermNodeOperation { UNDEF, BITWISE_NOT, MINUS, EXPRESSION, L_VALUE, R_VALUE };

  ArithmeticTermNode() = default;

  ArithmeticTermNode(size_t line_number, ArithmeticTermNodeOperation operation, AstNode* term)
      : AstNode{Kind::ARITHMETIC_TERM, line_number}, operation_{operation}, term_{term} {}

  ArithmeticTermNode(size_t line_number, ArithmeticTermNodeOperation operation, ArithmeticTermNode* arithmetic_term)
      : AstNode{Kind::ARITHMETIC_TERM, line_number}, operation_{operation}, term_{arithmetic_term} {}

  ArithmeticTermNode(size_t line_number, ArithmeticExpressionNode* arithmetic_expression);

  ArithmeticTermNode(size_t line_number, LValueNode* l_value)
      : AstNode{Kind::ARITHMETIC_TERM, line_number}, operation_{ArithmeticTermNodeOperation::L_VALUE}, term_{l_value} {}

  ArithmeticTermNode(size_t line_number, RValueNode* r_value)
      : AstNode{Kind::ARITHMETIC_TERM, line_number}, operation_{ArithmeticTermNodeOperation::R_VALUE}, term_{r_value} {}

  ArithmeticTermNode(const ArithmeticTermNode&) = delete;
  ArithmeticTermNode(ArithmeticTermNode&&) = default;

  ArithmeticTermNode& operator=(const ArithmeticTermNode&) = delete;
  ArithmeticTermNode& operator=(ArithmeticTermNode&&) = default;

  ~ArithmeticTermNode() = default;

  static bool classof(const ArithmeticTermNode* node) { return node->getKind() == ast::Kind::ARITHMETIC_TERM; }

  ArithmeticTermNodeOperation getOperation() const { return operation_; }
  const std::unique_ptr<AstNode>& getTerm() const { return term_; }

  void accept(class AstVisitor* visitor) const override { visitor->visit(this); }
  [[nodiscard]] virtual std::unique_ptr<AstNode> clone() const override;
  void print(std::ostream& out, int tab) const override;

 private:
  ArithmeticTermNodeOperation operation_;
  std::unique_ptr<AstNode> term_;
};
}  // namespace ast

#endif  // AST_ARITHMETIC_TERM_NODE_HPP
