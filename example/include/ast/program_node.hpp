#ifndef AST_PROGRAM_NODE_HPP
#define AST_PROGRAM_NODE_HPP

#include "ast_node.hpp"
#include "ast_visitor.hpp"
#include "expression_side_node.hpp"

namespace ast {
class ProgramNode : public AstNode {
 public:
  
    
  ProgramNode() = default;
    
  ProgramNode(ExpressionSideNode* expression_side):
    expression_side_{expression_side}{}

  ProgramNode(const ProgramNode&) = delete;
  ProgramNode(ProgramNode&&) = default;
    
  ProgramNode& operator=(const ProgramNode&) = delete;
  ProgramNode& operator=(ProgramNode&&) = default;
    
  ~ProgramNode() = default;
  
  const std::unique_ptr<ExpressionSideNode>& getExpressionSide() const { return expression_side_; }

  void accept(class AstVisitor* visitor) const override { visitor->visit(this); }
  [[nodiscard]] virtual std::unique_ptr<AstNode> clone() const override;
  void print(std::ostream& out, int tab) const override;
  
 private:
  std::unique_ptr<ExpressionSideNode> expression_side_;
};
}  // namespace ast

#endif  // AST_PROGRAM_NODE_HPP
