#ifndef AST_ARITHMETIC_EXPRESSION_NODE_HPP
#define AST_ARITHMETIC_EXPRESSION_NODE_HPP

#include "arithmetic_expr_lvl1_node.hpp"
#include "ast_node.hpp"
#include "ast_visitor.hpp"

namespace ast {
class ArithmeticExpressionNode : public AstNode {
 public:
  enum class ArithmeticExpressionNodeOperation { UNDEF, BITWISE_OR, EXPRESSION };

  ArithmeticExpressionNode() = default;

  ArithmeticExpressionNode(size_t line_number, ArithmeticExpressionNode* arithmetic_expression,
                           ArithmeticExpressionNodeOperation operation, ArithmeticExprLvl1Node* arithmetic_expr_lvl_1)
      : AstNode{Kind::ARITHMETIC_EXPRESSION, line_number},
        arithmetic_expression_{arithmetic_expression},
        operation_{operation},
        arithmetic_expr_lvl_1_{arithmetic_expr_lvl_1} {}

  ArithmeticExpressionNode(size_t line_number, ArithmeticExprLvl1Node* arithmetic_expr_lvl_1)
      : AstNode{Kind::ARITHMETIC_EXPRESSION, line_number},
        operation_{ArithmeticExpressionNodeOperation::EXPRESSION},
        arithmetic_expr_lvl_1_{arithmetic_expr_lvl_1} {}

  ArithmeticExpressionNode(const ArithmeticExpressionNode&) = delete;
  ArithmeticExpressionNode(ArithmeticExpressionNode&&) = default;

  ArithmeticExpressionNode& operator=(const ArithmeticExpressionNode&) = delete;
  ArithmeticExpressionNode& operator=(ArithmeticExpressionNode&&) = default;

  ~ArithmeticExpressionNode() = default;

  static bool classof(const ArithmeticExpressionNode* node) { return node->getKind() == ast::Kind::ARITHMETIC_EXPRESSION; }

  const std::unique_ptr<ArithmeticExpressionNode>& getArithmeticExpression() const { return arithmetic_expression_; }
  ArithmeticExpressionNodeOperation getOperation() const { return operation_; }
  const std::unique_ptr<ArithmeticExprLvl1Node>& getArithmeticExprLvl1() const { return arithmetic_expr_lvl_1_; }

  void accept(class AstVisitor* visitor) const override { visitor->visit(this); }
  [[nodiscard]] virtual std::unique_ptr<AstNode> clone() const override;
  void print(std::ostream& out, int tab) const override;

 private:
  std::unique_ptr<ArithmeticExpressionNode> arithmetic_expression_;
  ArithmeticExpressionNodeOperation operation_;
  std::unique_ptr<ArithmeticExprLvl1Node> arithmetic_expr_lvl_1_;
};
}  // namespace ast

#endif  // AST_ARITHMETIC_EXPRESSION_NODE_HPP
