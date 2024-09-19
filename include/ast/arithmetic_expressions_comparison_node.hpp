#ifndef AST_ARITHMETIC_EXPRESSIONS_COMPARISON_NODE_HPP
#define AST_ARITHMETIC_EXPRESSIONS_COMPARISON_NODE_HPP

#include "arithmetic_expression_node.hpp"
#include "ast_node.hpp"
#include "ast_visitor.hpp"

namespace ast {
class ArithmeticExpressionsComparisonNode : public AstNode {
 public:
  enum class ArithmeticExpressionsComparisonNodeOperation {
    UNDEF,
    GREATER_THAN,
    LESS_THAN_EQUAL,
    GREATER_THAN_EQUAL,
    LESS_THAN,
    NOT_EQUAL,
    EQUAL
  };

  ArithmeticExpressionsComparisonNode() = default;

  ArithmeticExpressionsComparisonNode(size_t line_number, ArithmeticExpressionNode* arithmetic_expression1,
                                      ArithmeticExpressionsComparisonNodeOperation operation,
                                      ArithmeticExpressionNode* arithmetic_expression2)
      : AstNode{Kind::ARITHMETIC_EXPRESSIONS_COMPARISON, line_number},
        arithmetic_expression1_{arithmetic_expression1},
        operation_{operation},
        arithmetic_expression2_{arithmetic_expression2} {}

  ArithmeticExpressionsComparisonNode(const ArithmeticExpressionsComparisonNode&) = delete;
  ArithmeticExpressionsComparisonNode(ArithmeticExpressionsComparisonNode&&) = default;

  ArithmeticExpressionsComparisonNode& operator=(const ArithmeticExpressionsComparisonNode&) = delete;
  ArithmeticExpressionsComparisonNode& operator=(ArithmeticExpressionsComparisonNode&&) = default;

  ~ArithmeticExpressionsComparisonNode() = default;

  static bool classof(const ArithmeticExpressionsComparisonNode* node) {
    return node->getKind() == ast::Kind::ARITHMETIC_EXPRESSIONS_COMPARISON;
  }

  const std::unique_ptr<ArithmeticExpressionNode>& getArithmeticExpression1() const { return arithmetic_expression1_; }
  ArithmeticExpressionsComparisonNodeOperation getOperation() const { return operation_; }
  const std::unique_ptr<ArithmeticExpressionNode>& getArithmeticExpression2() const { return arithmetic_expression2_; }

  void accept(class AstVisitor* visitor) const override { visitor->visit(this); }
  [[nodiscard]] virtual std::unique_ptr<AstNode> clone() const override;
  void print(std::ostream& out, int tab) const override;

 private:
  std::unique_ptr<ArithmeticExpressionNode> arithmetic_expression1_;
  ArithmeticExpressionsComparisonNodeOperation operation_;
  std::unique_ptr<ArithmeticExpressionNode> arithmetic_expression2_;
};
}  // namespace ast

#endif  // AST_ARITHMETIC_EXPRESSIONS_COMPARISON_NODE_HPP
