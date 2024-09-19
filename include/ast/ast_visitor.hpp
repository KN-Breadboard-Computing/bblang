#ifndef AST_VISITOR_HPP
#define AST_VISITOR_HPP

namespace ast {
class ArithmeticExprLvl1Node;
class ArithmeticExprLvl2Node;
class LogicExprLvl1Node;
class ArithmeticExpressionNode;
class LogicExpressionNode;
class LValueNode;
class LogicConstantNode;
class RValueNode;
class ArithmeticExprLvl5Node;
class ArithmeticExpressionsComparisonNode;
class RealNode;
class ProgramNode;
class LogicTermNode;
class ArithmeticExprLvl4Node;
class ArithmeticConstantNode;
class ArithmeticTermNode;
class IntegerNode;
class ArithmeticExprLvl3Node;
class LogicExprLvl2Node;
class IdentifierNode;

class AstVisitor {
 public:
  AstVisitor() = default;
    
  AstVisitor(const AstVisitor&) = default;
  AstVisitor(AstVisitor&&) = default;
    
  AstVisitor& operator=(const AstVisitor&) = default;
  AstVisitor& operator=(AstVisitor&&) = default;
    
  virtual ~AstVisitor() = default;
    
  virtual void visit(const ast::ArithmeticExprLvl1Node*) = 0;
  virtual void visit(const ast::ArithmeticExprLvl2Node*) = 0;
  virtual void visit(const ast::LogicExprLvl1Node*) = 0;
  virtual void visit(const ast::ArithmeticExpressionNode*) = 0;
  virtual void visit(const ast::LogicExpressionNode*) = 0;
  virtual void visit(const ast::LValueNode*) = 0;
  virtual void visit(const ast::LogicConstantNode*) = 0;
  virtual void visit(const ast::RValueNode*) = 0;
  virtual void visit(const ast::ArithmeticExprLvl5Node*) = 0;
  virtual void visit(const ast::ArithmeticExpressionsComparisonNode*) = 0;
  virtual void visit(const ast::RealNode*) = 0;
  virtual void visit(const ast::ProgramNode*) = 0;
  virtual void visit(const ast::LogicTermNode*) = 0;
  virtual void visit(const ast::ArithmeticExprLvl4Node*) = 0;
  virtual void visit(const ast::ArithmeticConstantNode*) = 0;
  virtual void visit(const ast::ArithmeticTermNode*) = 0;
  virtual void visit(const ast::IntegerNode*) = 0;
  virtual void visit(const ast::ArithmeticExprLvl3Node*) = 0;
  virtual void visit(const ast::LogicExprLvl2Node*) = 0;
  virtual void visit(const ast::IdentifierNode*) = 0;

};
}  // namespace ast

#endif  // AST_VISITOR_HPP
