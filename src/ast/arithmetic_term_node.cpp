#include "../../include/ast/arithmetic_term_node.hpp"

namespace ast {
std::ostream& operator<<(std::ostream& os, ArithmeticTermNode::ArithmeticTermNodeOperation name) {
  switch (name) {
    case ArithmeticTermNode::ArithmeticTermNodeOperation::UNDEF:
      os << "UNDEF";
      break;
    case ArithmeticTermNode::ArithmeticTermNodeOperation::BITWISE_NOT:
      os << "BITWISE_NOT";
      break;
    case ArithmeticTermNode::ArithmeticTermNodeOperation::MINUS:
      os << "MINUS";
      break;
    case ArithmeticTermNode::ArithmeticTermNodeOperation::EXPRESSION:
      os << "EXPRESSION";
      break;
    case ArithmeticTermNode::ArithmeticTermNodeOperation::L_VALUE:
      os << "L_VALUE";
      break;
    case ArithmeticTermNode::ArithmeticTermNodeOperation::R_VALUE:
      os << "R_VALUE";
      break;
  }
  return os;
}

ArithmeticTermNode::ArithmeticTermNode(size_t line_number, ArithmeticExpressionNode* arithmetic_expression)
    : AstNode{Kind::ARITHMETIC_TERM, line_number},
      operation_{ArithmeticTermNodeOperation::EXPRESSION},
      term_{arithmetic_expression} {}

[[nodiscard]] std::unique_ptr<AstNode> ArithmeticTermNode::clone() const {
  AstNode* new_arithmetic_term = term_ ? term_->clone().release() : nullptr;

  return std::make_unique<ArithmeticTermNode>(getLineNumber(), operation_, std::move(new_arithmetic_term));
}

void ArithmeticTermNode::print(std::ostream& out, int tab) const {
  out << std::string(tab, ' ') << "ArithmeticTermNode" << std::endl;
  out << std::string(tab, ' ') << "ArithmeticTermNodeOperation: " << operation_ << std::endl;
  if (term_) {
    term_->print(out, tab + 2);
  }
  else {
    out << std::string(tab + 2, ' ') << "nullptr" << std::endl;
  }
}
}  // namespace ast
