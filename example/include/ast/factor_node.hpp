#ifndef AST_FACTOR_NODE_HPP
#define AST_FACTOR_NODE_HPP

#include "ast_node.hpp"
#include "ast_visitor.hpp"
#include "integer_node.hpp"

namespace ast {
class FactorNode : public AstNode {
 public:
  enum class FactorNodeOperation { UNDEF, MINUS, INT };
    
  FactorNode() = default;
    
  FactorNode(FactorNodeOperation operation, FactorNode* factor):
    operation_{operation},
    factor_{factor}{}

  FactorNode(IntegerNode* integer):
    operation_{FactorNodeOperation::INT},
    factor_{integer}{}

  FactorNode(const FactorNode&) = delete;
  FactorNode(FactorNode&&) = default;
    
  FactorNode& operator=(const FactorNode&) = delete;
  FactorNode& operator=(FactorNode&&) = default;
    
  ~FactorNode() = default;
  
  FactorNodeOperation getOperation() const { return operation_; }
  const std::unique_ptr<AstNode>& getFactor() const { return factor_; }

  void accept(class AstVisitor* visitor) const override { visitor->visit(this); }
  [[nodiscard]] virtual std::unique_ptr<AstNode> clone() const override;
  void print(std::ostream& out, int tab) const override;
  
 private:
  FactorNodeOperation operation_;
  std::unique_ptr<AstNode> factor_;
};
}  // namespace ast

#endif  // AST_FACTOR_NODE_HPP
