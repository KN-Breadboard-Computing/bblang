#ifndef AST_LOGIC_EXPR_LVL2_NODE_HPP
#define AST_LOGIC_EXPR_LVL2_NODE_HPP

#include "ast_node.hpp"
#include "ast_visitor.hpp"
#include "logic_term_node.hpp"

namespace ast {
class LogicExprLvl2Node : public AstNode {
 public:
  enum class LogicExprLvl2NodeOperation { UNDEF, AND, EXPRESSION };

  LogicExprLvl2Node() = default;

  LogicExprLvl2Node(size_t line_number, LogicTermNode* logic_term1, LogicExprLvl2NodeOperation operation,
                    LogicTermNode* logic_term2)
      : AstNode{Kind::LOGIC_EXPR_LVL2, line_number},
        logic_term1_{logic_term1},
        operation_{operation},
        logic_term2_{logic_term2} {}

  LogicExprLvl2Node(size_t line_number, LogicTermNode* logic_term)
      : AstNode{Kind::LOGIC_EXPR_LVL2, line_number},
        logic_term1_{logic_term},
        operation_{LogicExprLvl2NodeOperation::EXPRESSION} {}

  LogicExprLvl2Node(const LogicExprLvl2Node&) = delete;
  LogicExprLvl2Node(LogicExprLvl2Node&&) = default;

  LogicExprLvl2Node& operator=(const LogicExprLvl2Node&) = delete;
  LogicExprLvl2Node& operator=(LogicExprLvl2Node&&) = default;

  ~LogicExprLvl2Node() = default;

  static bool classof(const LogicExprLvl2Node* node) { return node->getKind() == ast::Kind::LOGIC_EXPR_LVL2; }

  const std::unique_ptr<LogicTermNode>& getLogicTerm1() const { return logic_term1_; }
  LogicExprLvl2NodeOperation getOperation() const { return operation_; }
  const std::unique_ptr<LogicTermNode>& getLogicTerm2() const { return logic_term2_; }

  void accept(class AstVisitor* visitor) const override { visitor->visit(this); }
  [[nodiscard]] virtual std::unique_ptr<AstNode> clone() const override;
  void print(std::ostream& out, int tab) const override;

 private:
  std::unique_ptr<LogicTermNode> logic_term1_;
  LogicExprLvl2NodeOperation operation_;
  std::unique_ptr<LogicTermNode> logic_term2_;
};
}  // namespace ast

#endif  // AST_LOGIC_EXPR_LVL2_NODE_HPP
