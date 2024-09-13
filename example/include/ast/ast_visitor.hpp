#ifndef AST_VISITOR_HPP
#define AST_VISITOR_HPP

namespace ast {
class ExpressionSideNode;
class IntegerNode;
class ProgramNode;
class TermNode;
class FactorNode;

class AstVisitor {
 public:
  AstVisitor() = default;
    
  AstVisitor(const AstVisitor&) = default;
  AstVisitor(AstVisitor&&) = default;
    
  AstVisitor& operator=(const AstVisitor&) = default;
  AstVisitor& operator=(AstVisitor&&) = default;
    
  virtual ~AstVisitor() = default;
    
  virtual void visit(const ast::ExpressionSideNode*) = 0;
  virtual void visit(const ast::IntegerNode*) = 0;
  virtual void visit(const ast::ProgramNode*) = 0;
  virtual void visit(const ast::TermNode*) = 0;
  virtual void visit(const ast::FactorNode*) = 0;

};
}  // namespace ast

#endif  // AST_VISITOR_HPP
