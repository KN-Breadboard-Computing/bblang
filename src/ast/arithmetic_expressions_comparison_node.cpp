#include "../../include/ast/arithmetic_expressions_comparison_node.hpp"

namespace ast {
std::ostream& operator<<(std::ostream& os,
                         ArithmeticExpressionsComparisonNode::ArithmeticExpressionsComparisonNodeOperation name) {
  switch (name) {
    case ArithmeticExpressionsComparisonNode::ArithmeticExpressionsComparisonNodeOperation::UNDEF:
      os << "UNDEF";
      break;
    case ArithmeticExpressionsComparisonNode::ArithmeticExpressionsComparisonNodeOperation::GREATER_THAN:
      os << "GREATER_THAN";
      break;
    case ArithmeticExpressionsComparisonNode::ArithmeticExpressionsComparisonNodeOperation::LESS_THAN_EQUAL:
      os << "LESS_THAN_EQUAL";
      break;
    case ArithmeticExpressionsComparisonNode::ArithmeticExpressionsComparisonNodeOperation::GREATER_THAN_EQUAL:
      os << "GREATER_THAN_EQUAL";
      break;
    case ArithmeticExpressionsComparisonNode::ArithmeticExpressionsComparisonNodeOperation::LESS_THAN:
      os << "LESS_THAN";
      break;
    case ArithmeticExpressionsComparisonNode::ArithmeticExpressionsComparisonNodeOperation::NOT_EQUAL:
      os << "NOT_EQUAL";
      break;
    case ArithmeticExpressionsComparisonNode::ArithmeticExpressionsComparisonNodeOperation::EQUAL:
      os << "EQUAL";
      break;
  }
  return os;
}

[[nodiscard]] std::unique_ptr<AstNode> ArithmeticExpressionsComparisonNode::clone() const {
  ArithmeticExpressionNode* new_arithmetic_expression1 =
      arithmetic_expression1_ ? dynamic_cast<ArithmeticExpressionNode*>(arithmetic_expression1_->clone().release()) : nullptr;
  ArithmeticExpressionNode* new_arithmetic_expression2 =
      arithmetic_expression2_ ? dynamic_cast<ArithmeticExpressionNode*>(arithmetic_expression2_->clone().release()) : nullptr;

  return std::make_unique<ArithmeticExpressionsComparisonNode>(getLineNumber(), std::move(new_arithmetic_expression1), operation_,
                                                               std::move(new_arithmetic_expression2));
}

void ArithmeticExpressionsComparisonNode::print(std::ostream& out, int tab) const {
  out << std::string(tab, ' ') << "ArithmeticExpressionsComparisonNode" << std::endl;
  if (arithmetic_expression1_) {
    arithmetic_expression1_->print(out, tab + 2);
  }
  else {
    out << std::string(tab + 2, ' ') << "nullptr" << std::endl;
  }
  out << std::string(tab, ' ') << "ArithmeticExpressionsComparisonNodeOperation: " << operation_ << std::endl;
  if (arithmetic_expression2_) {
    arithmetic_expression2_->print(out, tab + 2);
  }
  else {
    out << std::string(tab + 2, ' ') << "nullptr" << std::endl;
  }
}
}  // namespace ast
