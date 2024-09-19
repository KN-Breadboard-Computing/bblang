#ifndef CODE_GEN_CONTEXT_HPP
#define CODE_GEN_CONTEXT_HPP

#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"

namespace code_gen {
class Context {
 public:
  Context();

  Context(const Context&) = delete;
  Context(Context&&) = delete;

  Context& operator=(const Context&) = delete;
  Context& operator=(Context&&) = delete;

  ~Context();

  llvm::Module* getModule() const { return module_; }
  llvm::LLVMContext& getGlobalContext() { return llvmContext_; }

 private:
  llvm::Module* module_{nullptr};
  llvm::LLVMContext llvmContext_;
};
}  // namespace code_gen

#endif  // CODE_GEN_CONTEXT_HPP
