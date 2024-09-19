#ifndef AST_LOGIC_EXPRESSION_NODE_HPP
#define AST_LOGIC_EXPRESSION_NODE_HPP

#include "ast_node.hpp"
#include "ast_visitor.hpp"
#include "logic_expr_lvl1_node.hpp"

namespace ast {
class LogicExpressionNode : public AstNode {
 public:
  enum class LogicExpressionNodeOperation { UNDEF, OR, EXPRESSION };

  LogicExpressionNode() = default;

  LogicExpressionNode(size_t line_number, LogicExpressionNode* logic_expression, LogicExpressionNodeOperation operation,
                      LogicExprLvl1Node* logic_expr_lvl_1)
      : AstNode{Kind::LOGIC_EXPRESSION, line_number},
        logic_expression_{logic_expression},
        operation_{operation},
        logic_expr_lvl_1_{logic_expr_lvl_1} {}

  LogicExpressionNode(size_t line_number, LogicExprLvl1Node* logic_expr_lvl_1)
      : AstNode{Kind::LOGIC_EXPRESSION, line_number},
        operation_{LogicExpressionNodeOperation::EXPRESSION},
        logic_expr_lvl_1_{logic_expr_lvl_1} {}

  LogicExpressionNode(const LogicExpressionNode&) = delete;
  LogicExpressionNode(LogicExpressionNode&&) = default;

  LogicExpressionNode& operator=(const LogicExpressionNode&) = delete;
  LogicExpressionNode& operator=(LogicExpressionNode&&) = default;

  ~LogicExpressionNode() = default;

  static bool classof(const LogicExpressionNode* node) { return node->getKind() == ast::Kind::LOGIC_EXPRESSION; }

  const std::unique_ptr<LogicExpressionNode>& getLogicExpression() const { return logic_expression_; }
  LogicExpressionNodeOperation getOperation() const { return operation_; }
  const std::unique_ptr<LogicExprLvl1Node>& getLogicExprLvl1() const { return logic_expr_lvl_1_; }

  void accept(class AstVisitor* visitor) const override { visitor->visit(this); }
  [[nodiscard]] virtual std::unique_ptr<AstNode> clone() const override;
  void print(std::ostream& out, int tab) const override;

 private:
  std::unique_ptr<LogicExpressionNode> logic_expression_;
  LogicExpressionNodeOperation operation_;
  std::unique_ptr<LogicExprLvl1Node> logic_expr_lvl_1_;
};
}  // namespace ast

#endif  // AST_LOGIC_EXPRESSION_NODE_HPP
