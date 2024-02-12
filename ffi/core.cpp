#include "core.h"
#include <llvm-c/Support.h>
#include <llvm/Support/CBindingWrapping.h>
#include <llvm/IR/LLVMContext.h>

#include <cstdio>

extern "C" {

API_EXPORT(const char *)
LLVMPY_CreateString(const char *msg) { return strdup(msg); }

API_EXPORT(const char *)
LLVMPY_CreateByteString(const char *buf, size_t len) {
    char *dest = (char *)malloc(len + 1);
    if (dest != NULL) {
        memcpy(dest, buf, len);
        dest[len] = '\0';
    }
    return dest;
}

API_EXPORT(void)
LLVMPY_DisposeString(const char *msg) { free(const_cast<char *>(msg)); }

API_EXPORT(LLVMContextRef)
LLVMPY_GetGlobalContext(bool EnableOpaquePointers) {
#if (LLVM_VERSION_MAJOR >= 14)
  LLVMContextRef CR = LLVMGetGlobalContext();
  if (EnableOpaquePointers)
    llvm::unwrap(CR)->setOpaquePointers(true);
  return CR;
#else
  return LLVMGetGlobalContext();
#endif
}

API_EXPORT(LLVMContextRef)
LLVMPY_ContextCreate(bool EnableOpaquePointers) {
#if (LLVM_VERSION_MAJOR >= 14)
  LLVMContextRef CR = LLVMContextCreate();
  if (EnableOpaquePointers)
    llvm::unwrap(CR)->setOpaquePointers(true);
  return CR;
#else
  return LLVMContextCreate();
#endif
}

API_EXPORT(bool)
LLVMPY_SupportsTypedPointers(LLVMContextRef CTX) {
#if (LLVM_VERSION_MAJOR >= 14)
  return false;
#else
  return llvm::unwrap(CTX)->supportsTypedPointers();
#endif
}

API_EXPORT(void)
LLVMPY_ContextDispose(LLVMContextRef context) {
    return LLVMContextDispose(context);
}

API_EXPORT(void)
LLVMPY_SetCommandLine(const char *name, const char *option) {
    const char *argv[] = {name, option};
    LLVMParseCommandLineOptions(2, argv, NULL);
}

} // end extern "C"
