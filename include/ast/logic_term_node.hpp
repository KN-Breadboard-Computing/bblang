#ifndef AST_LOGIC_TERM_NODE_HPP
#define AST_LOGIC_TERM_NODE_HPP

#include "arithmetic_expressions_comparison_node.hpp"
#include "ast_node.hpp"
#include "ast_visitor.hpp"
#include "l_value_node.hpp"
#include "logic_expression_node.hpp"
#include "r_value_node.hpp"

namespace ast {
class LogicTermNode : public AstNode {
 public:
  enum class LogicTermNodeOperation { UNDEF, NOT, EXPRESSION, COMPARISON, LVALUE, RVALUE };

  LogicTermNode() = default;

  LogicTermNode(size_t line_number, LogicTermNodeOperation operation, AstNode* term)
      : AstNode{Kind::LOGIC_TERM, line_number}, operation_{operation}, term_{term} {}

  LogicTermNode(size_t line_number, LogicTermNodeOperation operation, LogicTermNode* logic_term)
      : AstNode{Kind::LOGIC_TERM, line_number}, operation_{operation}, term_{logic_term} {}

  LogicTermNode(size_t line_number, LogicExpressionNode* logic_expression);

  LogicTermNode(size_t line_number, ArithmeticExpressionsComparisonNode* arithmetic_expressions_comparison)
      : AstNode{Kind::LOGIC_TERM, line_number},
        operation_{LogicTermNodeOperation::COMPARISON},
        term_{arithmetic_expressions_comparison} {}

  LogicTermNode(size_t line_number, LValueNode* l_value)
      : AstNode{Kind::LOGIC_TERM, line_number}, operation_{LogicTermNodeOperation::LVALUE}, term_{l_value} {}

  LogicTermNode(size_t line_number, RValueNode* r_value)
      : AstNode{Kind::LOGIC_TERM, line_number}, operation_{LogicTermNodeOperation::RVALUE}, term_{r_value} {}

  LogicTermNode(const LogicTermNode&) = delete;
  LogicTermNode(LogicTermNode&&) = default;

  LogicTermNode& operator=(const LogicTermNode&) = delete;
  LogicTermNode& operator=(LogicTermNode&&) = default;

  ~LogicTermNode() = default;

  static bool classof(const LogicTermNode* node) { return node->getKind() == ast::Kind::LOGIC_TERM; }

  LogicTermNodeOperation getOperation() const { return operation_; }
  const std::unique_ptr<AstNode>& getTerm() const { return term_; }

  void accept(class AstVisitor* visitor) const override { visitor->visit(this); }
  [[nodiscard]] virtual std::unique_ptr<AstNode> clone() const override;
  void print(std::ostream& out, int tab) const override;

 private:
  LogicTermNodeOperation operation_;
  std::unique_ptr<AstNode> term_;
};
}  // namespace ast

#endif  // AST_LOGIC_TERM_NODE_HPP
