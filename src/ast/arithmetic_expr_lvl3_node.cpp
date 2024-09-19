#include "../../include/ast/arithmetic_expr_lvl3_node.hpp"

namespace ast {
std::ostream& operator<<(std::ostream& os, ArithmeticExprLvl3Node::ArithmeticExprLvl3NodeOperation name) {
  switch (name) {
    case ArithmeticExprLvl3Node::ArithmeticExprLvl3NodeOperation::UNDEF:
      os << "UNDEF";
      break;
    case ArithmeticExprLvl3Node::ArithmeticExprLvl3NodeOperation::SHIFT_LEFT:
      os << "SHIFT_LEFT";
      break;
    case ArithmeticExprLvl3Node::ArithmeticExprLvl3NodeOperation::SHIFT_RIGHT:
      os << "SHIFT_RIGHT";
      break;
    case ArithmeticExprLvl3Node::ArithmeticExprLvl3NodeOperation::EXPRESSION:
      os << "EXPRESSION";
      break;
  }
  return os;
}

[[nodiscard]] std::unique_ptr<AstNode> ArithmeticExprLvl3Node::clone() const {
  ArithmeticExprLvl3Node* new_arithmetic_expr_lvl_3 =
      arithmetic_expr_lvl_3_ ? dynamic_cast<ArithmeticExprLvl3Node*>(arithmetic_expr_lvl_3_->clone().release()) : nullptr;
  ArithmeticExprLvl4Node* new_arithmetic_expr_lvl_4 =
      arithmetic_expr_lvl_4_ ? dynamic_cast<ArithmeticExprLvl4Node*>(arithmetic_expr_lvl_4_->clone().release()) : nullptr;

  return std::make_unique<ArithmeticExprLvl3Node>(getLineNumber(), std::move(new_arithmetic_expr_lvl_3), operation_,
                                                  std::move(new_arithmetic_expr_lvl_4));
}

void ArithmeticExprLvl3Node::print(std::ostream& out, int tab) const {
  out << std::string(tab, ' ') << "ArithmeticExprLvl3Node" << std::endl;
  if (arithmetic_expr_lvl_3_) {
    arithmetic_expr_lvl_3_->print(out, tab + 2);
  }
  else {
    out << std::string(tab + 2, ' ') << "nullptr" << std::endl;
  }
  out << std::string(tab, ' ') << "ArithmeticExprLvl3NodeOperation: " << operation_ << std::endl;
  if (arithmetic_expr_lvl_4_) {
    arithmetic_expr_lvl_4_->print(out, tab + 2);
  }
  else {
    out << std::string(tab + 2, ' ') << "nullptr" << std::endl;
  }
}
}  // namespace ast
