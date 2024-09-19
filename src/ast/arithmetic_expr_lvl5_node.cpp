#include "../../include/ast/arithmetic_expr_lvl5_node.hpp"

namespace ast {
std::ostream& operator<<(std::ostream& os, ArithmeticExprLvl5Node::ArithmeticExprLvl5NodeOperation name) {
  switch (name) {
    case ArithmeticExprLvl5Node::ArithmeticExprLvl5NodeOperation::UNDEF:
      os << "UNDEF";
      break;
    case ArithmeticExprLvl5Node::ArithmeticExprLvl5NodeOperation::DIVIDE:
      os << "DIVIDE";
      break;
    case ArithmeticExprLvl5Node::ArithmeticExprLvl5NodeOperation::MOD:
      os << "MOD";
      break;
    case ArithmeticExprLvl5Node::ArithmeticExprLvl5NodeOperation::MULTIPLY:
      os << "MULTIPLY";
      break;
    case ArithmeticExprLvl5Node::ArithmeticExprLvl5NodeOperation::EXPRESSION:
      os << "EXPRESSION";
      break;
  }
  return os;
}

[[nodiscard]] std::unique_ptr<AstNode> ArithmeticExprLvl5Node::clone() const {
  ArithmeticExprLvl5Node* new_arithmetic_expr_lvl_5 =
      arithmetic_expr_lvl_5_ ? dynamic_cast<ArithmeticExprLvl5Node*>(arithmetic_expr_lvl_5_->clone().release()) : nullptr;
  ArithmeticTermNode* new_arithmetic_term =
      arithmetic_term_ ? dynamic_cast<ArithmeticTermNode*>(arithmetic_term_->clone().release()) : nullptr;

  return std::make_unique<ArithmeticExprLvl5Node>(getLineNumber(), std::move(new_arithmetic_expr_lvl_5), operation_,
                                                  std::move(new_arithmetic_term));
}

void ArithmeticExprLvl5Node::print(std::ostream& out, int tab) const {
  out << std::string(tab, ' ') << "ArithmeticExprLvl5Node" << std::endl;
  if (arithmetic_expr_lvl_5_) {
    arithmetic_expr_lvl_5_->print(out, tab + 2);
  }
  else {
    out << std::string(tab + 2, ' ') << "nullptr" << std::endl;
  }
  out << std::string(tab, ' ') << "ArithmeticExprLvl5NodeOperation: " << operation_ << std::endl;
  if (arithmetic_term_) {
    arithmetic_term_->print(out, tab + 2);
  }
  else {
    out << std::string(tab + 2, ' ') << "nullptr" << std::endl;
  }
}
}  // namespace ast
