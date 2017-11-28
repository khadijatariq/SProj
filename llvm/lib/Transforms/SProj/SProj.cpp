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
      FuncTy_1_args.push_back(PointerTy_1);

      FunctionType* FuncTy_1 = FunctionType::get(
        /*Result=*/Type::getVoidTy(M.getContext()),
        /*Params=*/FuncTy_1_args,
        /*isVarArg=*/false);
      Constant *c1 = M.getOrInsertFunction("_Z12getInputTypePcS_",
          FuncTy_1);
      Function* func_itype = cast<Function>(c1);

      FunctionType* FuncTy_2 = FunctionType::get(
        /*Result=*/Type::getVoidTy(M.getContext()),
        /*Params=*/FuncTy_1_args,
        /*isVarArg=*/false);
      Constant *c2 = M.getOrInsertFunction("_Z13getReturnTypePcS_",
          FuncTy_2);
      Function* func_rtype = cast<Function>(c2);

      std::vector<Type*>FuncTy_2_args;
      FuncTy_2_args.push_back(PointerTy_1);
      FuncTy_2_args.push_back(IntegerType::get(M.getContext(), 32));
      FunctionType* FuncTy_3 = FunctionType::get(
        /*Result=*/Type::getVoidTy(M.getContext()),
        /*Params=*/FuncTy_2_args,
        /*isVarArg=*/false);
      Constant *c3 = M.getOrInsertFunction("_Z6getIntPci",
          FuncTy_3);
      Function* func_int = cast<Function>(c3);

      for (Module::iterator modI = M.begin(), modE = M.end(); modI != modE; ++modI) {
        if (!(modI->isDeclaration() || (modI->getName() == "main"))){
          IRBuilder<> builder(&modI->getEntryBlock(), modI->getEntryBlock().begin());
          Value *strPtr1 = builder.CreateGlobalStringPtr(modI->getName());
          std::string ret_type;
          raw_string_ostream rsor(ret_type);
          modI->getReturnType()->print(rsor);
          Value *strPtr2 = builder.CreateGlobalStringPtr(rsor.str());
          Value* args1[] = {strPtr1,strPtr2};
          builder.CreateCall(func_rtype, args1);
          for (Function::arg_iterator argI = modI->arg_begin(), argE = modI->arg_end(); argI != argE; ++argI) {
            std::string input_type;
            raw_string_ostream rsoi(input_type);
            argI->getType()->print(rsoi);
            strPtr2 = builder.CreateGlobalStringPtr(rsoi.str());
            Value* args2[] = {strPtr1,strPtr2};
            builder.CreateCall(func_itype, args2);
            Value* args3[] = {strPtr1,argI};
            builder.CreateCall(func_int, args3);
          }
        }
      }
      return false;
    }
  };
}

char SProj::ID = 0;
static RegisterPass<SProj> X("sproj", "Count Dynamic Instructions Pass", false, false);