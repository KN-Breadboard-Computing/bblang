#include "../../include/ast/logic_constant_node.hpp"

namespace ast {
std::ostream& operator<<(std::ostream& os, LogicConstantNode::LogicConstantNodeOperation name) {
  switch (name) {
    case LogicConstantNode::LogicConstantNodeOperation::UNDEF:
      os << "UNDEF";
      break;
    case LogicConstantNode::LogicConstantNodeOperation::FALSE:
      os << "FALSE";
      break;
    case LogicConstantNode::LogicConstantNodeOperation::TRUE:
      os << "TRUE";
      break;
  }
  return os;
}

[[nodiscard]] std::unique_ptr<AstNode> LogicConstantNode::clone() const {

  return std::make_unique<LogicConstantNode>(getLineNumber(), operation_);
}

void LogicConstantNode::print(std::ostream& out, int tab) const {
  out << std::string(tab, ' ') << "LogicConstantNode" << std::endl;
  out << std::string(tab, ' ') << "LogicConstantNodeOperation: " << operation_ << std::endl;
}
}  // namespace ast
