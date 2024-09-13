#ifndef AST_TERM_NODE_HPP
#define AST_TERM_NODE_HPP

#include "ast_node.hpp"
#include "ast_visitor.hpp"
#include "factor_node.hpp"

namespace ast {
class TermNode : public AstNode {
 public:
  enum class TermNodeOperation { UNDEF, MULTIPLY, FACTOR };
    
  TermNode() = default;
    
  TermNode(TermNode* term, TermNodeOperation operation, FactorNode* factor):
    term_{term},
    operation_{operation},
    factor_{factor}{}

  TermNode(FactorNode* factor):
    operation_{TermNodeOperation::FACTOR},
    factor_{factor}{}

  TermNode(const TermNode&) = delete;
  TermNode(TermNode&&) = default;
    
  TermNode& operator=(const TermNode&) = delete;
  TermNode& operator=(TermNode&&) = default;
    
  ~TermNode() = default;
  
  const std::unique_ptr<TermNode>& getTerm() const { return term_; }
  TermNodeOperation getOperation() const { return operation_; }
  const std::unique_ptr<FactorNode>& getFactor() const { return factor_; }

  void accept(class AstVisitor* visitor) const override { visitor->visit(this); }
  [[nodiscard]] virtual std::unique_ptr<AstNode> clone() const override;
  void print(std::ostream& out, int tab) const override;
  
 private:
  std::unique_ptr<TermNode> term_;
  TermNodeOperation operation_;
  std::unique_ptr<FactorNode> factor_;
};
}  // namespace ast

#endif  // AST_TERM_NODE_HPP
