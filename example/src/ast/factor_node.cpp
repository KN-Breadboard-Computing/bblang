#include "../../include/ast/factor_node.hpp"

namespace ast {
std::ostream& operator<<(std::ostream& os, FactorNode::FactorNodeOperation name) {
  switch (name) {
    case FactorNode::FactorNodeOperation::UNDEF:
      os << "UNDEF";
      break;
    case FactorNode::FactorNodeOperation::MINUS:
      os << "MINUS";
      break;
    case FactorNode::FactorNodeOperation::INT:
      os << "INT";
      break;
  }
  return os;
}

[[nodiscard]] std::unique_ptr<AstNode> FactorNode::clone() const {
  FactorNode* new_factor = factor_ ? dynamic_cast<FactorNode*>(factor_->clone().release()) : nullptr;

  return std::make_unique<FactorNode>(operation_, std::move(new_factor));
}

void FactorNode::print(std::ostream& out, int tab) const {
  out << std::string(tab, ' ') << "FactorNode" << std::endl;
  out << std::string(tab, ' ') << "FactorNodeOperation: " << operation_ << std::endl;
  if (factor_) {
    factor_->print(out, tab + 2);
  }
  else {
    out << std::string(tab + 2, ' ') << "nullptr" << std::endl;
  }
}
}  // namespace ast
