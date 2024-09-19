#ifndef AST_AST_NODE_HPP
#define AST_AST_NODE_HPP

#include "ast_kind.hpp"

#include <memory>
#include <ostream>

namespace ast {
class AstNode {
 public:
  AstNode() : id_{id_counter_++}, kind_{Kind::UNDEF}, line_number_{0} {}
  AstNode(Kind kind, size_t line_number) : id_{id_counter_++}, kind_{kind}, line_number_{line_number} {}

  AstNode(const AstNode&) = delete;
  AstNode(AstNode&&) = default;

  AstNode& operator=(const AstNode&) = delete;
  AstNode& operator=(AstNode&&) = default;

  virtual ~AstNode() = default;

  [[nodiscard]] size_t getId() const { return id_; }
  [[nodiscard]] Kind getKind() const { return kind_; }
  [[nodiscard]] size_t getLineNumber() const { return line_number_; }

  virtual void accept(class AstVisitor* visitor) const = 0;
  [[nodiscard]] virtual std::unique_ptr<AstNode> clone() const = 0;
  virtual void print(std::ostream& out, int tab) const = 0;

  friend std::ostream& operator<<(std::ostream& out, const AstNode& node) {
    node.print(out, 0);
    return out;
  }

 private:
  static size_t id_counter_;

  size_t id_;
  Kind kind_;
  size_t line_number_;
};
}  // namespace ast

#endif  // AST_AST_NODE_HPP
