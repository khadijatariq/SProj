#include "llvm/Pass.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/Support/raw_ostream.h"

using namespace llvm;

namespace {
  struct SProj : public ModulePass {
    static char ID;
    SProj() : ModulePass(ID) {}
    
    bool runOnModule(Module &M) override {
      std::vector<Type*>FuncTy_1_args;
      PointerType* PointerTy_1 = PointerType::get(IntegerType::get(M.getContext(), 8), 0);
      FuncTy_1_args.push_back(PointerTy_1);
      FuncTy_1_args.push_back(IntegerType::get(M.getContext(), 32));
      FuncTy_1_args.push_back(IntegerType::get(M.getContext(), 32));
      FuncTy_1_args.push_back(IntegerType::get(M.getContext(), 32));
      FunctionType* FuncTy_1 = FunctionType::get(
        /*Result=*/Type::getVoidTy(M.getContext()),
        /*Params=*/FuncTy_1_args,
        /*isVarArg=*/false);
      Constant *c1 = M.getOrInsertFunction("_Z6getSetPciii",
          FuncTy_1);
      Function* func_set = cast<Function>(c1);

      std::vector<Type*>FuncTy_2_args;
      FunctionType* FuncTy_2 = FunctionType::get(
        /*Result=*/Type::getVoidTy(M.getContext()),
        /*Params=*/FuncTy_2_args,
        /*isVarArg=*/false);
      Constant *c2 = M.getOrInsertFunction("_Z10initializev",
          FuncTy_2);
      Function* func_init = cast<Function>(c2);

      std::vector<Type*>FuncTy_3_args;
      FunctionType* FuncTy_3 = FunctionType::get(
        /*Result=*/Type::getVoidTy(M.getContext()),
        /*Params=*/FuncTy_3_args,
        /*isVarArg=*/false);
      Constant *c3 = M.getOrInsertFunction("_Z5storev",
          FuncTy_3);
      Function* func_store = cast<Function>(c3);

      for (Module::iterator modI = M.begin(), modE = M.end(); modI != modE; ++modI) {
        if (!(modI->isDeclaration() || (modI->getName() == "main"))){
          for (BasicBlock &BB : *modI) {
            for (Instruction &I : BB) {
              if (auto* op = dyn_cast<ReturnInst>(&I)) {
                IRBuilder<> builder(op);
                Value *strPtr1 = builder.CreateGlobalStringPtr(modI->getName());
                Function::arg_iterator argI = modI->arg_begin();
                Value* args1[] = {strPtr1,argI,argI+1,op->getReturnValue()};
                builder.CreateCall(func_set, args1);
              }
            }
          }
        } else if (modI->getName() == "main") {
          
        }
      }
      return false;
    }
  };
}

char SProj::ID = 0;
static RegisterPass<SProj> X("sproj", "Count Dynamic Instructions Pass", false, false);