#include "../../include/ast/program_node.hpp"
    
namespace ast {

[[nodiscard]] std::unique_ptr<AstNode> ProgramNode::clone() const {
  ExpressionSideNode* new_expression_side = expression_side_ ? dynamic_cast<ExpressionSideNode*>(expression_side_->clone().release()) : nullptr;

  return std::make_unique<ProgramNode>(std::move(new_expression_side));
}
    
void ProgramNode::print(std::ostream& out, int tab) const {
  out << std::string(tab, ' ') << "ProgramNode" << std::endl;
  if (expression_side_) {
    expression_side_->print(out, tab + 2);
  }
  else {
    out << std::string(tab + 2, ' ') << "nullptr" << std::endl;
  }

}
} // namespace ast
