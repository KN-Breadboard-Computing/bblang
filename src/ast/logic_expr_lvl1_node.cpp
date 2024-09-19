#include "../../include/ast/logic_expr_lvl1_node.hpp"

namespace ast {
std::ostream& operator<<(std::ostream& os, LogicExprLvl1Node::LogicExprLvl1NodeOperation name) {
  switch (name) {
    case LogicExprLvl1Node::LogicExprLvl1NodeOperation::UNDEF:
      os << "UNDEF";
      break;
    case LogicExprLvl1Node::LogicExprLvl1NodeOperation::XOR:
      os << "XOR";
      break;
    case LogicExprLvl1Node::LogicExprLvl1NodeOperation::EXPRESSION:
      os << "EXPRESSION";
      break;
  }
  return os;
}

[[nodiscard]] std::unique_ptr<AstNode> LogicExprLvl1Node::clone() const {
  LogicExprLvl1Node* new_logic_expr_lvl_1 =
      logic_expr_lvl_1_ ? dynamic_cast<LogicExprLvl1Node*>(logic_expr_lvl_1_->clone().release()) : nullptr;
  LogicExprLvl2Node* new_logic_expr_lvl_2 =
      logic_expr_lvl_2_ ? dynamic_cast<LogicExprLvl2Node*>(logic_expr_lvl_2_->clone().release()) : nullptr;

  return std::make_unique<LogicExprLvl1Node>(getLineNumber(), std::move(new_logic_expr_lvl_1), operation_,
                                             std::move(new_logic_expr_lvl_2));
}

void LogicExprLvl1Node::print(std::ostream& out, int tab) const {
  out << std::string(tab, ' ') << "LogicExprLvl1Node" << std::endl;
  if (logic_expr_lvl_1_) {
    logic_expr_lvl_1_->print(out, tab + 2);
  }
  else {
    out << std::string(tab + 2, ' ') << "nullptr" << std::endl;
  }
  out << std::string(tab, ' ') << "LogicExprLvl1NodeOperation: " << operation_ << std::endl;
  if (logic_expr_lvl_2_) {
    logic_expr_lvl_2_->print(out, tab + 2);
  }
  else {
    out << std::string(tab + 2, ' ') << "nullptr" << std::endl;
  }
}
}  // namespace ast
