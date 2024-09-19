#include "../../include/ast/arithmetic_expr_lvl4_node.hpp"

namespace ast {
std::ostream& operator<<(std::ostream& os, ArithmeticExprLvl4Node::ArithmeticExprLvl4NodeOperation name) {
  switch (name) {
    case ArithmeticExprLvl4Node::ArithmeticExprLvl4NodeOperation::UNDEF:
      os << "UNDEF";
      break;
    case ArithmeticExprLvl4Node::ArithmeticExprLvl4NodeOperation::MINUS:
      os << "MINUS";
      break;
    case ArithmeticExprLvl4Node::ArithmeticExprLvl4NodeOperation::PLUS:
      os << "PLUS";
      break;
    case ArithmeticExprLvl4Node::ArithmeticExprLvl4NodeOperation::EXPRESSION:
      os << "EXPRESSION";
      break;
  }
  return os;
}

[[nodiscard]] std::unique_ptr<AstNode> ArithmeticExprLvl4Node::clone() const {
  ArithmeticExprLvl4Node* new_arithmetic_expr_lvl_4 =
      arithmetic_expr_lvl_4_ ? dynamic_cast<ArithmeticExprLvl4Node*>(arithmetic_expr_lvl_4_->clone().release()) : nullptr;
  ArithmeticExprLvl5Node* new_arithmetic_expr_lvl_5 =
      arithmetic_expr_lvl_5_ ? dynamic_cast<ArithmeticExprLvl5Node*>(arithmetic_expr_lvl_5_->clone().release()) : nullptr;

  return std::make_unique<ArithmeticExprLvl4Node>(getLineNumber(), std::move(new_arithmetic_expr_lvl_4), operation_,
                                                  std::move(new_arithmetic_expr_lvl_5));
}

void ArithmeticExprLvl4Node::print(std::ostream& out, int tab) const {
  out << std::string(tab, ' ') << "ArithmeticExprLvl4Node" << std::endl;
  if (arithmetic_expr_lvl_4_) {
    arithmetic_expr_lvl_4_->print(out, tab + 2);
  }
  else {
    out << std::string(tab + 2, ' ') << "nullptr" << std::endl;
  }
  out << std::string(tab, ' ') << "ArithmeticExprLvl4NodeOperation: " << operation_ << std::endl;
  if (arithmetic_expr_lvl_5_) {
    arithmetic_expr_lvl_5_->print(out, tab + 2);
  }
  else {
    out << std::string(tab + 2, ' ') << "nullptr" << std::endl;
  }
}
}  // namespace ast
