#ifndef CALCULATOR_HPP
#define CALCULATOR_HPP

#include "include/ast/ast_visitor.hpp"
#include "include/ast/expression_side_node.hpp"
#include "include/ast/factor_node.hpp"
#include "include/ast/integer_node.hpp"
#include "include/ast/program_node.hpp"
#include "include/ast/term_node.hpp"

#include <stack>

class Calculator : public ast::AstVisitor {
 public:
  Calculator() = default;

  Calculator(const Calculator&) = delete;
  Calculator(Calculator&&) = delete;

  Calculator& operator=(const Calculator&) = delete;
  Calculator& operator=(Calculator&&) = delete;

  ~Calculator() = default;

  int calc(const ast::ProgramNode* program) {
    program->accept(this);
    return stack_.top();
  }

 private:
  std::stack<int> stack_;

  void visit(const ast::IntegerNode* integer) override { stack_.push(integer->getValue()); }

  void visit(const ast::ProgramNode* program) override { program->getExpressionSide()->accept(this); }

  void visit(const ast::FactorNode* factor) override {
    switch (factor->getOperation()) {
      case ast::FactorNode::FactorNodeOperation::INT: {
        factor->getFactor()->accept(this);
        break;
      }
      case ast::FactorNode::FactorNodeOperation::MINUS: {
        factor->getFactor()->accept(this);
        int arg = stack_.top();
        stack_.pop();
        stack_.push(-arg);
        break;
      }
      default:
        throw std::runtime_error("Undefined operation");
    }
  }

  void visit(const ast::ExpressionSideNode* expression_side) override {
    switch (expression_side->getOperation()) {
      case ast::ExpressionSideNode::ExpressionSideNodeOperation::PLUS: {
        expression_side->getExpressionSide()->accept(this);
        expression_side->getTerm()->accept(this);
        int arg1 = stack_.top();
        stack_.pop();
        int arg2 = stack_.top();
        stack_.pop();
        stack_.push(arg1 + arg2);
        break;
      }
      case ast::ExpressionSideNode::ExpressionSideNodeOperation::MINUS: {
        expression_side->getExpressionSide()->accept(this);
        expression_side->getTerm()->accept(this);
        int arg1 = stack_.top();
        stack_.pop();
        int arg2 = stack_.top();
        stack_.pop();
        stack_.push(arg2 - arg1);
        break;
      }
      case ast::ExpressionSideNode::ExpressionSideNodeOperation::TERM: {
        expression_side->getTerm()->accept(this);
        break;
      }
      default:
        throw std::runtime_error("Undefined operation");
    }
  }

  void visit(const ast::TermNode* term) override {
    switch (term->getOperation()) {
      case ast::TermNode::TermNodeOperation::MULTIPLY: {
        term->getTerm()->accept(this);
        term->getFactor()->accept(this);
        int arg1 = stack_.top();
        stack_.pop();
        int arg2 = stack_.top();
        stack_.pop();
        stack_.push(arg1 * arg2);
        break;
      }
      case ast::TermNode::TermNodeOperation::FACTOR: {
        term->getFactor()->accept(this);
        break;
      }
      default:
        throw std::runtime_error("Undefined operation");
    }
  }
};

#endif  // CALCULATOR_HPP
