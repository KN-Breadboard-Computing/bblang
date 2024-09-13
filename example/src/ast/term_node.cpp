#include "../../include/ast/term_node.hpp"

namespace ast {
std::ostream& operator<<(std::ostream& os, TermNode::TermNodeOperation name) {
  switch (name) {
    case TermNode::TermNodeOperation::UNDEF:
      os << "UNDEF";
      break;
    case TermNode::TermNodeOperation::MULTIPLY:
      os << "MULTIPLY";
      break;
    case TermNode::TermNodeOperation::FACTOR:
      os << "FACTOR";
      break;
  }
  return os;
}

[[nodiscard]] std::unique_ptr<AstNode> TermNode::clone() const {
  TermNode* new_term = term_ ? dynamic_cast<TermNode*>(term_->clone().release()) : nullptr;
  FactorNode* new_factor = factor_ ? dynamic_cast<FactorNode*>(factor_->clone().release()) : nullptr;

  return std::make_unique<TermNode>(std::move(new_term), operation_, std::move(new_factor));
}

void TermNode::print(std::ostream& out, int tab) const {
  out << std::string(tab, ' ') << "TermNode" << std::endl;
  if (term_) {
    term_->print(out, tab + 2);
  }
  else {
    out << std::string(tab + 2, ' ') << "nullptr" << std::endl;
  }
  out << std::string(tab, ' ') << "TermNodeOperation: " << operation_ << std::endl;
  if (factor_) {
    factor_->print(out, tab + 2);
  }
  else {
    out << std::string(tab + 2, ' ') << "nullptr" << std::endl;
  }
}
}  // namespace ast
