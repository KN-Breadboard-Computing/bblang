#ifndef AST_EXPRESSION_SIDE_NODE_HPP
#define AST_EXPRESSION_SIDE_NODE_HPP

#include "ast_node.hpp"
#include "ast_visitor.hpp"
#include "term_node.hpp"

namespace ast {
class ExpressionSideNode : public AstNode {
 public:
  enum class ExpressionSideNodeOperation { UNDEF, MINUS, PLUS, TERM };
    
  ExpressionSideNode() = default;
    
  ExpressionSideNode(ExpressionSideNode* expression_side, ExpressionSideNodeOperation operation, TermNode* term):
    expression_side_{expression_side},
    operation_{operation},
    term_{term}{}

  ExpressionSideNode(TermNode* term):
    operation_{ExpressionSideNodeOperation::TERM},
    term_{term}{}

  ExpressionSideNode(const ExpressionSideNode&) = delete;
  ExpressionSideNode(ExpressionSideNode&&) = default;
    
  ExpressionSideNode& operator=(const ExpressionSideNode&) = delete;
  ExpressionSideNode& operator=(ExpressionSideNode&&) = default;
    
  ~ExpressionSideNode() = default;
  
  const std::unique_ptr<ExpressionSideNode>& getExpressionSide() const { return expression_side_; }
  ExpressionSideNodeOperation getOperation() const { return operation_; }
  const std::unique_ptr<TermNode>& getTerm() const { return term_; }

  void accept(class AstVisitor* visitor) const override { visitor->visit(this); }
  [[nodiscard]] virtual std::unique_ptr<AstNode> clone() const override;
  void print(std::ostream& out, int tab) const override;
  
 private:
  std::unique_ptr<ExpressionSideNode> expression_side_;
  ExpressionSideNodeOperation operation_;
  std::unique_ptr<TermNode> term_;
};
}  // namespace ast

#endif  // AST_EXPRESSION_SIDE_NODE_HPP
