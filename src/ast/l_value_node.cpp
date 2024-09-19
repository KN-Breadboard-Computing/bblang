#include "../../include/ast/l_value_node.hpp"

namespace ast {

[[nodiscard]] std::unique_ptr<AstNode> LValueNode::clone() const {
  IdentifierNode* new_identifier = identifier_ ? dynamic_cast<IdentifierNode*>(identifier_->clone().release()) : nullptr;

  return std::make_unique<LValueNode>(getLineNumber(), std::move(new_identifier));
}

void LValueNode::print(std::ostream& out, int tab) const {
  out << std::string(tab, ' ') << "LValueNode" << std::endl;
  if (identifier_) {
    identifier_->print(out, tab + 2);
  }
  else {
    out << std::string(tab + 2, ' ') << "nullptr" << std::endl;
  }
}
}  // namespace ast
