#include "../../include/ast/logic_expr_lvl2_node.hpp"

namespace ast {
std::ostream& operator<<(std::ostream& os, LogicExprLvl2Node::LogicExprLvl2NodeOperation name) {
  switch (name) {
    case LogicExprLvl2Node::LogicExprLvl2NodeOperation::UNDEF:
      os << "UNDEF";
      break;
    case LogicExprLvl2Node::LogicExprLvl2NodeOperation::AND:
      os << "AND";
      break;
    case LogicExprLvl2Node::LogicExprLvl2NodeOperation::EXPRESSION:
      os << "EXPRESSION";
      break;
  }
  return os;
}

[[nodiscard]] std::unique_ptr<AstNode> LogicExprLvl2Node::clone() const {
  LogicTermNode* new_logic_term1 = logic_term1_ ? dynamic_cast<LogicTermNode*>(logic_term1_->clone().release()) : nullptr;
  LogicTermNode* new_logic_term2 = logic_term2_ ? dynamic_cast<LogicTermNode*>(logic_term2_->clone().release()) : nullptr;

  return std::make_unique<LogicExprLvl2Node>(getLineNumber(), std::move(new_logic_term1), operation_, std::move(new_logic_term2));
}

void LogicExprLvl2Node::print(std::ostream& out, int tab) const {
  out << std::string(tab, ' ') << "LogicExprLvl2Node" << std::endl;
  if (logic_term1_) {
    logic_term1_->print(out, tab + 2);
  }
  else {
    out << std::string(tab + 2, ' ') << "nullptr" << std::endl;
  }
  out << std::string(tab, ' ') << "LogicExprLvl2NodeOperation: " << operation_ << std::endl;
  if (logic_term2_) {
    logic_term2_->print(out, tab + 2);
  }
  else {
    out << std::string(tab + 2, ' ') << "nullptr" << std::endl;
  }
}
}  // namespace ast
