#include "../../include/ast/r_value_node.hpp"

namespace ast {

[[nodiscard]] std::unique_ptr<AstNode> RValueNode::clone() const {
  AstNode* new_value = value_ ? value_->clone().release() : nullptr;

  return std::make_unique<RValueNode>(getLineNumber(), std::move(new_value));
}

void RValueNode::print(std::ostream& out, int tab) const {
  out << std::string(tab, ' ') << "RValueNode" << std::endl;
  if (value_) {
    value_->print(out, tab + 2);
  }
  else {
    out << std::string(tab + 2, ' ') << "nullptr" << std::endl;
  }
}
}  // namespace ast
