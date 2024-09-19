#ifndef AST_ARITHMETIC_EXPR_LVL3_NODE_HPP
#define AST_ARITHMETIC_EXPR_LVL3_NODE_HPP

#include "arithmetic_expr_lvl4_node.hpp"
#include "ast_node.hpp"
#include "ast_visitor.hpp"

namespace ast {
class ArithmeticExprLvl3Node : public AstNode {
 public:
  enum class ArithmeticExprLvl3NodeOperation { UNDEF, SHIFT_LEFT, SHIFT_RIGHT, EXPRESSION };

  ArithmeticExprLvl3Node() = default;

  ArithmeticExprLvl3Node(size_t line_number, ArithmeticExprLvl3Node* arithmetic_expr_lvl_3,
                         ArithmeticExprLvl3NodeOperation operation, ArithmeticExprLvl4Node* arithmetic_expr_lvl_4)
      : AstNode{Kind::ARITHMETIC_EXPR_LVL3, line_number},
        arithmetic_expr_lvl_3_{arithmetic_expr_lvl_3},
        operation_{operation},
        arithmetic_expr_lvl_4_{arithmetic_expr_lvl_4} {}

  ArithmeticExprLvl3Node(size_t line_number, ArithmeticExprLvl4Node* arithmetic_expr_lvl_4)
      : AstNode{Kind::ARITHMETIC_EXPR_LVL3, line_number},
        operation_{ArithmeticExprLvl3NodeOperation::EXPRESSION},
        arithmetic_expr_lvl_4_{arithmetic_expr_lvl_4} {}

  ArithmeticExprLvl3Node(const ArithmeticExprLvl3Node&) = delete;
  ArithmeticExprLvl3Node(ArithmeticExprLvl3Node&&) = default;

  ArithmeticExprLvl3Node& operator=(const ArithmeticExprLvl3Node&) = delete;
  ArithmeticExprLvl3Node& operator=(ArithmeticExprLvl3Node&&) = default;

  ~ArithmeticExprLvl3Node() = default;

  static bool classof(const ArithmeticExprLvl3Node* node) { return node->getKind() == ast::Kind::ARITHMETIC_EXPR_LVL3; }

  const std::unique_ptr<ArithmeticExprLvl3Node>& getArithmeticExprLvl3() const { return arithmetic_expr_lvl_3_; }
  ArithmeticExprLvl3NodeOperation getOperation() const { return operation_; }
  const std::unique_ptr<ArithmeticExprLvl4Node>& getArithmeticExprLvl4() const { return arithmetic_expr_lvl_4_; }

  void accept(class AstVisitor* visitor) const override { visitor->visit(this); }
  [[nodiscard]] virtual std::unique_ptr<AstNode> clone() const override;
  void print(std::ostream& out, int tab) const override;

 private:
  std::unique_ptr<ArithmeticExprLvl3Node> arithmetic_expr_lvl_3_;
  ArithmeticExprLvl3NodeOperation operation_;
  std::unique_ptr<ArithmeticExprLvl4Node> arithmetic_expr_lvl_4_;
};
}  // namespace ast

#endif  // AST_ARITHMETIC_EXPR_LVL3_NODE_HPP
