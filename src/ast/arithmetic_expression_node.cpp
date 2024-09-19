#include "../../include/ast/arithmetic_expression_node.hpp"

namespace ast {
std::ostream& operator<<(std::ostream& os, ArithmeticExpressionNode::ArithmeticExpressionNodeOperation name) {
  switch (name) {
    case ArithmeticExpressionNode::ArithmeticExpressionNodeOperation::UNDEF:
      os << "UNDEF";
      break;
    case ArithmeticExpressionNode::ArithmeticExpressionNodeOperation::BITWISE_OR:
      os << "BITWISE_OR";
      break;
    case ArithmeticExpressionNode::ArithmeticExpressionNodeOperation::EXPRESSION:
      os << "EXPRESSION";
      break;
  }
  return os;
}

[[nodiscard]] std::unique_ptr<AstNode> ArithmeticExpressionNode::clone() const {
  ArithmeticExpressionNode* new_arithmetic_expression =
      arithmetic_expression_ ? dynamic_cast<ArithmeticExpressionNode*>(arithmetic_expression_->clone().release()) : nullptr;
  ArithmeticExprLvl1Node* new_arithmetic_expr_lvl_1 =
      arithmetic_expr_lvl_1_ ? dynamic_cast<ArithmeticExprLvl1Node*>(arithmetic_expr_lvl_1_->clone().release()) : nullptr;

  return std::make_unique<ArithmeticExpressionNode>(getLineNumber(), std::move(new_arithmetic_expression), operation_,
                                                    std::move(new_arithmetic_expr_lvl_1));
}

void ArithmeticExpressionNode::print(std::ostream& out, int tab) const {
  out << std::string(tab, ' ') << "ArithmeticExpressionNode" << std::endl;
  if (arithmetic_expression_) {
    arithmetic_expression_->print(out, tab + 2);
  }
  else {
    out << std::string(tab + 2, ' ') << "nullptr" << std::endl;
  }
  out << std::string(tab, ' ') << "ArithmeticExpressionNodeOperation: " << operation_ << std::endl;
  if (arithmetic_expr_lvl_1_) {
    arithmetic_expr_lvl_1_->print(out, tab + 2);
  }
  else {
    out << std::string(tab + 2, ' ') << "nullptr" << std::endl;
  }
}
}  // namespace ast
