#include "../../include/ast/logic_expression_node.hpp"

namespace ast {
std::ostream& operator<<(std::ostream& os, LogicExpressionNode::LogicExpressionNodeOperation name) {
  switch (name) {
    case LogicExpressionNode::LogicExpressionNodeOperation::UNDEF:
      os << "UNDEF";
      break;
    case LogicExpressionNode::LogicExpressionNodeOperation::OR:
      os << "OR";
      break;
    case LogicExpressionNode::LogicExpressionNodeOperation::EXPRESSION:
      os << "EXPRESSION";
      break;
  }
  return os;
}

[[nodiscard]] std::unique_ptr<AstNode> LogicExpressionNode::clone() const {
  LogicExpressionNode* new_logic_expression =
      logic_expression_ ? dynamic_cast<LogicExpressionNode*>(logic_expression_->clone().release()) : nullptr;
  LogicExprLvl1Node* new_logic_expr_lvl_1 =
      logic_expr_lvl_1_ ? dynamic_cast<LogicExprLvl1Node*>(logic_expr_lvl_1_->clone().release()) : nullptr;

  return std::make_unique<LogicExpressionNode>(getLineNumber(), std::move(new_logic_expression), operation_,
                                               std::move(new_logic_expr_lvl_1));
}

void LogicExpressionNode::print(std::ostream& out, int tab) const {
  out << std::string(tab, ' ') << "LogicExpressionNode" << std::endl;
  if (logic_expression_) {
    logic_expression_->print(out, tab + 2);
  }
  else {
    out << std::string(tab + 2, ' ') << "nullptr" << std::endl;
  }
  out << std::string(tab, ' ') << "LogicExpressionNodeOperation: " << operation_ << std::endl;
  if (logic_expr_lvl_1_) {
    logic_expr_lvl_1_->print(out, tab + 2);
  }
  else {
    out << std::string(tab + 2, ' ') << "nullptr" << std::endl;
  }
}
}  // namespace ast
