#include "../../include/ast/program_node.hpp"

namespace ast {

[[nodiscard]] std::unique_ptr<AstNode> ProgramNode::clone() const {
  AstNode* new_expression = expression_ ? expression_->clone().release() : nullptr;

  return std::make_unique<ProgramNode>(getLineNumber(), std::move(new_expression));
}

void ProgramNode::print(std::ostream& out, int tab) const {
  out << std::string(tab, ' ') << "ProgramNode" << std::endl;
  if (expression_) {
    expression_->print(out, tab + 2);
  }
  else {
    out << std::string(tab + 2, ' ') << "nullptr" << std::endl;
  }
}
}  // namespace ast
