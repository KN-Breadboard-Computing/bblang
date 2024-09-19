#include "../../include/ast/logic_term_node.hpp"

namespace ast {
std::ostream& operator<<(std::ostream& os, LogicTermNode::LogicTermNodeOperation name) {
  switch (name) {
    case LogicTermNode::LogicTermNodeOperation::UNDEF:
      os << "UNDEF";
      break;
    case LogicTermNode::LogicTermNodeOperation::NOT:
      os << "NOT";
      break;
    case LogicTermNode::LogicTermNodeOperation::EXPRESSION:
      os << "EXPRESSION";
      break;
    case LogicTermNode::LogicTermNodeOperation::COMPARISON:
      os << "COMPARISON";
      break;
    case LogicTermNode::LogicTermNodeOperation::LVALUE:
      os << "LVALUE";
      break;
    case LogicTermNode::LogicTermNodeOperation::RVALUE:
      os << "RVALUE";
      break;
  }
  return os;
}

LogicTermNode::LogicTermNode(size_t line_number, LogicExpressionNode* logic_expression)
    : AstNode{Kind::LOGIC_TERM, line_number}, operation_{LogicTermNodeOperation::EXPRESSION}, term_{logic_expression} {}

[[nodiscard]] std::unique_ptr<AstNode> LogicTermNode::clone() const {
  AstNode* new_logic_term = term_ ? term_->clone().release() : nullptr;

  return std::make_unique<LogicTermNode>(getLineNumber(), operation_, std::move(new_logic_term));
}

void LogicTermNode::print(std::ostream& out, int tab) const {
  out << std::string(tab, ' ') << "LogicTermNode" << std::endl;
  out << std::string(tab, ' ') << "LogicTermNodeOperation: " << operation_ << std::endl;
  if (term_) {
    term_->print(out, tab + 2);
  }
  else {
    out << std::string(tab + 2, ' ') << "nullptr" << std::endl;
  }
}
}  // namespace ast
