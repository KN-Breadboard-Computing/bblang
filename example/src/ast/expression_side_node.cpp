#include "../../include/ast/expression_side_node.hpp"

namespace ast {
std::ostream& operator<<(std::ostream& os, ExpressionSideNode::ExpressionSideNodeOperation name) {
  switch (name) {
    case ExpressionSideNode::ExpressionSideNodeOperation::UNDEF:
      os << "UNDEF";
      break;
    case ExpressionSideNode::ExpressionSideNodeOperation::MINUS:
      os << "MINUS";
      break;
    case ExpressionSideNode::ExpressionSideNodeOperation::PLUS:
      os << "PLUS";
      break;
    case ExpressionSideNode::ExpressionSideNodeOperation::TERM:
      os << "TERM";
      break;
  }
  return os;
}

[[nodiscard]] std::unique_ptr<AstNode> ExpressionSideNode::clone() const {
  ExpressionSideNode* new_expression_side =
      expression_side_ ? dynamic_cast<ExpressionSideNode*>(expression_side_->clone().release()) : nullptr;
  TermNode* new_term = term_ ? dynamic_cast<TermNode*>(term_->clone().release()) : nullptr;

  return std::make_unique<ExpressionSideNode>(std::move(new_expression_side), operation_, std::move(new_term));
}

void ExpressionSideNode::print(std::ostream& out, int tab) const {
  out << std::string(tab, ' ') << "ExpressionSideNode" << std::endl;
  if (expression_side_) {
    expression_side_->print(out, tab + 2);
  }
  else {
    out << std::string(tab + 2, ' ') << "nullptr" << std::endl;
  }
  out << std::string(tab, ' ') << "ExpressionSideNodeOperation: " << operation_ << std::endl;
  if (term_) {
    term_->print(out, tab + 2);
  }
  else {
    out << std::string(tab + 2, ' ') << "nullptr" << std::endl;
  }
}
}  // namespace ast
