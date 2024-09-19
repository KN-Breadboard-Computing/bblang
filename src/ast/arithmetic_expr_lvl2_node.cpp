#include "../../include/ast/arithmetic_expr_lvl2_node.hpp"

namespace ast {
std::ostream& operator<<(std::ostream& os, ArithmeticExprLvl2Node::ArithmeticExprLvl2NodeOperation name) {
  switch (name) {
    case ArithmeticExprLvl2Node::ArithmeticExprLvl2NodeOperation::UNDEF:
      os << "UNDEF";
      break;
    case ArithmeticExprLvl2Node::ArithmeticExprLvl2NodeOperation::BITWISE_AND:
      os << "BITWISE_AND";
      break;
    case ArithmeticExprLvl2Node::ArithmeticExprLvl2NodeOperation::EXPRESSION:
      os << "EXPRESSION";
      break;
  }
  return os;
}

[[nodiscard]] std::unique_ptr<AstNode> ArithmeticExprLvl2Node::clone() const {
  ArithmeticExprLvl2Node* new_arithmetic_expr_lvl_2 =
      arithmetic_expr_lvl_2_ ? dynamic_cast<ArithmeticExprLvl2Node*>(arithmetic_expr_lvl_2_->clone().release()) : nullptr;
  ArithmeticExprLvl3Node* new_arithmetic_expr_lvl_3 =
      arithmetic_expr_lvl_3_ ? dynamic_cast<ArithmeticExprLvl3Node*>(arithmetic_expr_lvl_3_->clone().release()) : nullptr;

  return std::make_unique<ArithmeticExprLvl2Node>(getLineNumber(), std::move(new_arithmetic_expr_lvl_2), operation_,
                                                  std::move(new_arithmetic_expr_lvl_3));
}

void ArithmeticExprLvl2Node::print(std::ostream& out, int tab) const {
  out << std::string(tab, ' ') << "ArithmeticExprLvl2Node" << std::endl;
  if (arithmetic_expr_lvl_2_) {
    arithmetic_expr_lvl_2_->print(out, tab + 2);
  }
  else {
    out << std::string(tab + 2, ' ') << "nullptr" << std::endl;
  }
  out << std::string(tab, ' ') << "ArithmeticExprLvl2NodeOperation: " << operation_ << std::endl;
  if (arithmetic_expr_lvl_3_) {
    arithmetic_expr_lvl_3_->print(out, tab + 2);
  }
  else {
    out << std::string(tab + 2, ' ') << "nullptr" << std::endl;
  }
}
}  // namespace ast
