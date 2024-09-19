#include "../../include/ast/arithmetic_constant_node.hpp"

namespace ast {

[[nodiscard]] std::unique_ptr<AstNode> ArithmeticConstantNode::clone() const {
  AstNode* new_number = number_ ? number_->clone().release() : nullptr;

  return std::make_unique<ArithmeticConstantNode>(getLineNumber(), std::move(new_number));
}

void ArithmeticConstantNode::print(std::ostream& out, int tab) const {
  out << std::string(tab, ' ') << "ArithmeticConstantNode" << std::endl;
  if (number_) {
    number_->print(out, tab + 2);
  }
  else {
    out << std::string(tab + 2, ' ') << "nullptr" << std::endl;
  }
}
}  // namespace ast
