#ifndef AST_ARITHMETIC_EXPR_LVL5_NODE_HPP
#define AST_ARITHMETIC_EXPR_LVL5_NODE_HPP

#include "arithmetic_term_node.hpp"
#include "ast_node.hpp"
#include "ast_visitor.hpp"

namespace ast {
class ArithmeticExprLvl5Node : public AstNode {
 public:
  enum class ArithmeticExprLvl5NodeOperation { UNDEF, DIVIDE, MOD, MULTIPLY, EXPRESSION };

  ArithmeticExprLvl5Node() = default;

  ArithmeticExprLvl5Node(size_t line_number, ArithmeticExprLvl5Node* arithmetic_expr_lvl_5,
                         ArithmeticExprLvl5NodeOperation operation, ArithmeticTermNode* arithmetic_term)
      : AstNode{Kind::ARITHMETIC_EXPR_LVL5, line_number},
        arithmetic_expr_lvl_5_{arithmetic_expr_lvl_5},
        operation_{operation},
        arithmetic_term_{arithmetic_term} {}

  ArithmeticExprLvl5Node(size_t line_number, ArithmeticTermNode* arithmetic_term)
      : AstNode{Kind::ARITHMETIC_EXPR_LVL5, line_number},
        operation_{ArithmeticExprLvl5NodeOperation::EXPRESSION},
        arithmetic_term_{arithmetic_term} {}

  ArithmeticExprLvl5Node(const ArithmeticExprLvl5Node&) = delete;
  ArithmeticExprLvl5Node(ArithmeticExprLvl5Node&&) = default;

  ArithmeticExprLvl5Node& operator=(const ArithmeticExprLvl5Node&) = delete;
  ArithmeticExprLvl5Node& operator=(ArithmeticExprLvl5Node&&) = default;

  ~ArithmeticExprLvl5Node() = default;

  static bool classof(const ArithmeticExprLvl5Node* node) { return node->getKind() == ast::Kind::ARITHMETIC_EXPR_LVL5; }

  const std::unique_ptr<ArithmeticExprLvl5Node>& getArithmeticExprLvl5() const { return arithmetic_expr_lvl_5_; }
  ArithmeticExprLvl5NodeOperation getOperation() const { return operation_; }
  const std::unique_ptr<ArithmeticTermNode>& getArithmeticTerm() const { return arithmetic_term_; }

  void accept(class AstVisitor* visitor) const override { visitor->visit(this); }
  [[nodiscard]] virtual std::unique_ptr<AstNode> clone() const override;
  void print(std::ostream& out, int tab) const override;

 private:
  std::unique_ptr<ArithmeticExprLvl5Node> arithmetic_expr_lvl_5_;
  ArithmeticExprLvl5NodeOperation operation_;
  std::unique_ptr<ArithmeticTermNode> arithmetic_term_;
};
}  // namespace ast

#endif  // AST_ARITHMETIC_EXPR_LVL5_NODE_HPP
