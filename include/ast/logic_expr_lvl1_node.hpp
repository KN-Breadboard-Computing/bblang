#ifndef AST_LOGIC_EXPR_LVL1_NODE_HPP
#define AST_LOGIC_EXPR_LVL1_NODE_HPP

#include "ast_node.hpp"
#include "ast_visitor.hpp"
#include "logic_expr_lvl2_node.hpp"

namespace ast {
class LogicExprLvl1Node : public AstNode {
 public:
  enum class LogicExprLvl1NodeOperation { UNDEF, XOR, EXPRESSION };

  LogicExprLvl1Node() = default;

  LogicExprLvl1Node(size_t line_number, LogicExprLvl1Node* logic_expr_lvl_1, LogicExprLvl1NodeOperation operation,
                    LogicExprLvl2Node* logic_expr_lvl_2)
      : AstNode{Kind::LOGIC_EXPR_LVL1, line_number},
        logic_expr_lvl_1_{logic_expr_lvl_1},
        operation_{operation},
        logic_expr_lvl_2_{logic_expr_lvl_2} {}

  LogicExprLvl1Node(size_t line_number, LogicExprLvl2Node* logic_expr_lvl_2)
      : AstNode{Kind::LOGIC_EXPR_LVL1, line_number},
        operation_{LogicExprLvl1NodeOperation::EXPRESSION},
        logic_expr_lvl_2_{logic_expr_lvl_2} {}

  LogicExprLvl1Node(const LogicExprLvl1Node&) = delete;
  LogicExprLvl1Node(LogicExprLvl1Node&&) = default;

  LogicExprLvl1Node& operator=(const LogicExprLvl1Node&) = delete;
  LogicExprLvl1Node& operator=(LogicExprLvl1Node&&) = default;

  ~LogicExprLvl1Node() = default;

  static bool classof(const LogicExprLvl1Node* node) { return node->getKind() == ast::Kind::LOGIC_EXPR_LVL1; }

  const std::unique_ptr<LogicExprLvl1Node>& getLogicExprLvl1() const { return logic_expr_lvl_1_; }
  LogicExprLvl1NodeOperation getOperation() const { return operation_; }
  const std::unique_ptr<LogicExprLvl2Node>& getLogicExprLvl2() const { return logic_expr_lvl_2_; }

  void accept(class AstVisitor* visitor) const override { visitor->visit(this); }
  [[nodiscard]] virtual std::unique_ptr<AstNode> clone() const override;
  void print(std::ostream& out, int tab) const override;

 private:
  std::unique_ptr<LogicExprLvl1Node> logic_expr_lvl_1_;
  LogicExprLvl1NodeOperation operation_;
  std::unique_ptr<LogicExprLvl2Node> logic_expr_lvl_2_;
};
}  // namespace ast

#endif  // AST_LOGIC_EXPR_LVL1_NODE_HPP
