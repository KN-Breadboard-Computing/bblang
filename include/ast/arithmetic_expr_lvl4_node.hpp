#ifndef AST_ARITHMETIC_EXPR_LVL4_NODE_HPP
#define AST_ARITHMETIC_EXPR_LVL4_NODE_HPP

#include "arithmetic_expr_lvl5_node.hpp"
#include "ast_node.hpp"
#include "ast_visitor.hpp"

namespace ast {
class ArithmeticExprLvl4Node : public AstNode {
 public:
  enum class ArithmeticExprLvl4NodeOperation { UNDEF, MINUS, PLUS, EXPRESSION };

  ArithmeticExprLvl4Node() = default;

  ArithmeticExprLvl4Node(size_t line_number, ArithmeticExprLvl4Node* arithmetic_expr_lvl_4,
                         ArithmeticExprLvl4NodeOperation operation, ArithmeticExprLvl5Node* arithmetic_expr_lvl_5)
      : AstNode{Kind::ARITHMETIC_EXPR_LVL4, line_number},
        arithmetic_expr_lvl_4_{arithmetic_expr_lvl_4},
        operation_{operation},
        arithmetic_expr_lvl_5_{arithmetic_expr_lvl_5} {}

  ArithmeticExprLvl4Node(size_t line_number, ArithmeticExprLvl5Node* arithmetic_expr_lvl_5)
      : AstNode{Kind::ARITHMETIC_EXPR_LVL4, line_number},
        operation_{ArithmeticExprLvl4NodeOperation::EXPRESSION},
        arithmetic_expr_lvl_5_{arithmetic_expr_lvl_5} {}

  ArithmeticExprLvl4Node(const ArithmeticExprLvl4Node&) = delete;
  ArithmeticExprLvl4Node(ArithmeticExprLvl4Node&&) = default;

  ArithmeticExprLvl4Node& operator=(const ArithmeticExprLvl4Node&) = delete;
  ArithmeticExprLvl4Node& operator=(ArithmeticExprLvl4Node&&) = default;

  ~ArithmeticExprLvl4Node() = default;

  static bool classof(const ArithmeticExprLvl4Node* node) { return node->getKind() == ast::Kind::ARITHMETIC_EXPR_LVL4; }

  const std::unique_ptr<ArithmeticExprLvl4Node>& getArithmeticExprLvl4() const { return arithmetic_expr_lvl_4_; }
  ArithmeticExprLvl4NodeOperation getOperation() const { return operation_; }
  const std::unique_ptr<ArithmeticExprLvl5Node>& getArithmeticExprLvl5() const { return arithmetic_expr_lvl_5_; }

  void accept(class AstVisitor* visitor) const override { visitor->visit(this); }
  [[nodiscard]] virtual std::unique_ptr<AstNode> clone() const override;
  void print(std::ostream& out, int tab) const override;

 private:
  std::unique_ptr<ArithmeticExprLvl4Node> arithmetic_expr_lvl_4_;
  ArithmeticExprLvl4NodeOperation operation_;
  std::unique_ptr<ArithmeticExprLvl5Node> arithmetic_expr_lvl_5_;
};
}  // namespace ast

#endif  // AST_ARITHMETIC_EXPR_LVL4_NODE_HPP
