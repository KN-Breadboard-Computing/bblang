#ifndef AST_ARITHMETIC_EXPR_LVL1_NODE_HPP
#define AST_ARITHMETIC_EXPR_LVL1_NODE_HPP

#include "arithmetic_expr_lvl2_node.hpp"
#include "ast_node.hpp"
#include "ast_visitor.hpp"

namespace ast {
class ArithmeticExprLvl1Node : public AstNode {
 public:
  enum class ArithmeticExprLvl1NodeOperation { UNDEF, BITWISE_XOR, EXPRESSION };

  ArithmeticExprLvl1Node() = default;

  ArithmeticExprLvl1Node(size_t line_number, ArithmeticExprLvl1Node* arithmetic_expr_lvl_1,
                         ArithmeticExprLvl1NodeOperation operation, ArithmeticExprLvl2Node* arithmetic_expr_lvl_2)
      : AstNode{Kind::ARITHMETIC_EXPR_LVL1, line_number},
        arithmetic_expr_lvl_1_{arithmetic_expr_lvl_1},
        operation_{operation},
        arithmetic_expr_lvl_2_{arithmetic_expr_lvl_2} {}

  ArithmeticExprLvl1Node(size_t line_number, ArithmeticExprLvl2Node* arithmetic_expr_lvl_2)
      : AstNode{Kind::ARITHMETIC_EXPR_LVL1, line_number},
        operation_{ArithmeticExprLvl1NodeOperation::EXPRESSION},
        arithmetic_expr_lvl_2_{arithmetic_expr_lvl_2} {}

  ArithmeticExprLvl1Node(const ArithmeticExprLvl1Node&) = delete;
  ArithmeticExprLvl1Node(ArithmeticExprLvl1Node&&) = default;

  ArithmeticExprLvl1Node& operator=(const ArithmeticExprLvl1Node&) = delete;
  ArithmeticExprLvl1Node& operator=(ArithmeticExprLvl1Node&&) = default;

  ~ArithmeticExprLvl1Node() = default;

  static bool classof(const ArithmeticExprLvl1Node* node) { return node->getKind() == ast::Kind::ARITHMETIC_EXPR_LVL1; }

  const std::unique_ptr<ArithmeticExprLvl1Node>& getArithmeticExprLvl1() const { return arithmetic_expr_lvl_1_; }
  ArithmeticExprLvl1NodeOperation getOperation() const { return operation_; }
  const std::unique_ptr<ArithmeticExprLvl2Node>& getArithmeticExprLvl2() const { return arithmetic_expr_lvl_2_; }

  void accept(class AstVisitor* visitor) const override { visitor->visit(this); }
  [[nodiscard]] virtual std::unique_ptr<AstNode> clone() const override;
  void print(std::ostream& out, int tab) const override;

 private:
  std::unique_ptr<ArithmeticExprLvl1Node> arithmetic_expr_lvl_1_;
  ArithmeticExprLvl1NodeOperation operation_;
  std::unique_ptr<ArithmeticExprLvl2Node> arithmetic_expr_lvl_2_;
};
}  // namespace ast

#endif  // AST_ARITHMETIC_EXPR_LVL1_NODE_HPP
