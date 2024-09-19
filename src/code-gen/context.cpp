#include "../../include/code-gen/code_gen.hpp"

#include "llvm/Support/ManagedStatic.h"
#include "llvm/Support/TargetSelect.h"

namespace code_gen {
Context::Context() {
  llvm::InitializeNativeTarget();
  llvm::InitializeNativeTargetAsmParser();
  llvm::InitializeNativeTargetAsmPrinter();
  module_ = new llvm::Module("bblang", llvmContext_);
}

Context::~Context() {
  llvm::llvm_shutdown();
}
}  // namespace code_gen
