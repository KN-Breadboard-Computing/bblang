#ifndef AST_ARITHMETIC_EXPR_LVL2_NODE_HPP
#define AST_ARITHMETIC_EXPR_LVL2_NODE_HPP

#include "arithmetic_expr_lvl3_node.hpp"
#include "ast_node.hpp"
#include "ast_visitor.hpp"

namespace ast {
class ArithmeticExprLvl2Node : public AstNode {
 public:
  enum class ArithmeticExprLvl2NodeOperation { UNDEF, BITWISE_AND, EXPRESSION };

  ArithmeticExprLvl2Node() = default;

  ArithmeticExprLvl2Node(size_t line_number, ArithmeticExprLvl2Node* arithmetic_expr_lvl_2,
                         ArithmeticExprLvl2NodeOperation operation, ArithmeticExprLvl3Node* arithmetic_expr_lvl_3)
      : AstNode{Kind::ARITHMETIC_EXPR_LVL2, line_number},
        arithmetic_expr_lvl_2_{arithmetic_expr_lvl_2},
        operation_{operation},
        arithmetic_expr_lvl_3_{arithmetic_expr_lvl_3} {}

  ArithmeticExprLvl2Node(size_t line_number, ArithmeticExprLvl3Node* arithmetic_expr_lvl_3)
      : AstNode{Kind::ARITHMETIC_EXPR_LVL2, line_number},
        operation_{ArithmeticExprLvl2NodeOperation::EXPRESSION},
        arithmetic_expr_lvl_3_{arithmetic_expr_lvl_3} {}

  ArithmeticExprLvl2Node(const ArithmeticExprLvl2Node&) = delete;
  ArithmeticExprLvl2Node(ArithmeticExprLvl2Node&&) = default;

  ArithmeticExprLvl2Node& operator=(const ArithmeticExprLvl2Node&) = delete;
  ArithmeticExprLvl2Node& operator=(ArithmeticExprLvl2Node&&) = default;

  ~ArithmeticExprLvl2Node() = default;

  static bool classof(const ArithmeticExprLvl2Node* node) { return node->getKind() == ast::Kind::ARITHMETIC_EXPR_LVL2; }

  const std::unique_ptr<ArithmeticExprLvl2Node>& getArithmeticExprLvl2() const { return arithmetic_expr_lvl_2_; }
  ArithmeticExprLvl2NodeOperation getOperation() const { return operation_; }
  const std::unique_ptr<ArithmeticExprLvl3Node>& getArithmeticExprLvl3() const { return arithmetic_expr_lvl_3_; }

  void accept(class AstVisitor* visitor) const override { visitor->visit(this); }
  [[nodiscard]] virtual std::unique_ptr<AstNode> clone() const override;
  void print(std::ostream& out, int tab) const override;

 private:
  std::unique_ptr<ArithmeticExprLvl2Node> arithmetic_expr_lvl_2_;
  ArithmeticExprLvl2NodeOperation operation_;
  std::unique_ptr<ArithmeticExprLvl3Node> arithmetic_expr_lvl_3_;
};
}  // namespace ast

#endif  // AST_ARITHMETIC_EXPR_LVL2_NODE_HPP
