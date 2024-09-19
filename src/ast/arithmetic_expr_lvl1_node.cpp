#include "../../include/ast/arithmetic_expr_lvl1_node.hpp"

namespace ast {
std::ostream& operator<<(std::ostream& os, ArithmeticExprLvl1Node::ArithmeticExprLvl1NodeOperation name) {
  switch (name) {
    case ArithmeticExprLvl1Node::ArithmeticExprLvl1NodeOperation::UNDEF:
      os << "UNDEF";
      break;
    case ArithmeticExprLvl1Node::ArithmeticExprLvl1NodeOperation::BITWISE_XOR:
      os << "BITWISE_XOR";
      break;
    case ArithmeticExprLvl1Node::ArithmeticExprLvl1NodeOperation::EXPRESSION:
      os << "EXPRESSION";
      break;
  }
  return os;
}

[[nodiscard]] std::unique_ptr<AstNode> ArithmeticExprLvl1Node::clone() const {
  ArithmeticExprLvl1Node* new_arithmetic_expr_lvl_1 =
      arithmetic_expr_lvl_1_ ? dynamic_cast<ArithmeticExprLvl1Node*>(arithmetic_expr_lvl_1_->clone().release()) : nullptr;
  ArithmeticExprLvl2Node* new_arithmetic_expr_lvl_2 =
      arithmetic_expr_lvl_2_ ? dynamic_cast<ArithmeticExprLvl2Node*>(arithmetic_expr_lvl_2_->clone().release()) : nullptr;

  return std::make_unique<ArithmeticExprLvl1Node>(getLineNumber(), std::move(new_arithmetic_expr_lvl_1), operation_,
                                                  std::move(new_arithmetic_expr_lvl_2));
}

void ArithmeticExprLvl1Node::print(std::ostream& out, int tab) const {
  out << std::string(tab, ' ') << "ArithmeticExprLvl1Node" << std::endl;
  if (arithmetic_expr_lvl_1_) {
    arithmetic_expr_lvl_1_->print(out, tab + 2);
  }
  else {
    out << std::string(tab + 2, ' ') << "nullptr" << std::endl;
  }
  out << std::string(tab, ' ') << "ArithmeticExprLvl1NodeOperation: " << operation_ << std::endl;
  if (arithmetic_expr_lvl_2_) {
    arithmetic_expr_lvl_2_->print(out, tab + 2);
  }
  else {
    out << std::string(tab + 2, ' ') << "nullptr" << std::endl;
  }
}
}  // namespace ast
