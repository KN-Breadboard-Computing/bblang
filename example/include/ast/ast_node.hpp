#ifndef AST_AST_NODE_HPP
#define AST_AST_NODE_HPP

#include <memory>
#include <ostream>

namespace ast {
class AstNode {
 public:
  AstNode() = default;

  AstNode(const AstNode&) = delete;
  AstNode(AstNode&&) = default;

  AstNode& operator=(const AstNode&) = delete;
  AstNode& operator=(AstNode&&) = default;

  virtual ~AstNode() = default;

  virtual void accept(class AstVisitor* visitor) const = 0;
  [[nodiscard]] virtual std::unique_ptr<AstNode> clone() const = 0;
  virtual void print(std::ostream & out, int tab) const = 0;

  friend std::ostream& operator<<(std::ostream& out, const AstNode& node) {
    node.print(out, 0);
    return out;
  }
};
}  // namespace ast

#endif  // AST_AST_NODE_HPP
