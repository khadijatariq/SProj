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

      FunctionType* FuncTy_2 = FunctionType::get(
        /*Result=*/Type::getVoidTy(M.getContext()),
        /*Params=*/FuncTy_1_args,
        /*isVarArg=*/false);
      Constant *c2 = M.getOrInsertFunction("_Z12getInputTypePcS_",
          FuncTy_2);
      Function* func_itype = cast<Function>(c2);

      FunctionType* FuncTy_3 = FunctionType::get(
        /*Result=*/Type::getVoidTy(M.getContext()),
        /*Params=*/FuncTy_1_args,
        /*isVarArg=*/false);
      Constant *c3 = M.getOrInsertFunction("_Z13getReturnTypePcPc",
          FuncTy_3);
      Function* func_rtype = cast<Function>(c3);

      std::vector<Type*>FuncTy_2_args;
      FuncTy_2_args.push_back(PointerTy_1);
      FuncTy_2_args.push_back(IntegerType::get(M.getContext(), 32));
      FunctionType* FuncTy_4 = FunctionType::get(
        /*Result=*/Type::getVoidTy(M.getContext()),
        /*Params=*/FuncTy_2_args,
        /*isVarArg=*/false);
      Constant *c4 = M.getOrInsertFunction("_Z6getIntPci",
          FuncTy_4);
      Function* func_int = cast<Function>(c4);

      for (Module::iterator modI = M.begin(), modE = M.end(); modI != modE; ++modI) {
        if (!(modI->isDeclaration() || (modI->getName() == "main"))){
          for (Function::arg_iterator argI = modI->arg_begin(), argE = modI->arg_end(); argI != argE; ++argI) {
            IRBuilder<> builder(inst_begin(modI));
            Value *strPtr1 = builder.CreateGlobalStringPtr(modI->getName());
            std::string type_str;
            raw_string_ostream rso(type_str);
            argI->getType()->print(rso);
            Value *strPtr2 = builder.CreateGlobalStringPtr(rso.str());
            Value* args1[] = {strPtr1,strPtr2};
            builder.CreateCall(func_itype, args1);
            Value* args2[] = {strPtr1,argI};
            builder.CreateCall(func_int, args2);
          }
        }
        // for (BasicBlock &funcI : *modI) {
        //   for (Instruction &I : funcI) {
        //     errs() << I.getOpcode() << "\n";
        //     if (I.getOpcode() == 31) {
        //       errs() << "here "<<I.getOpcodeName()<<"\n";
        //       // Insert *after* `op`.
        //       IRBuilder<> builder(&I);
        //       builder.SetInsertPoint(&funcI, ++builder.GetInsertPoint());

        //       // Insert a call to our function.
        //       Value* args[] = {&I};
        //       builder.CreateCall(func_add, args);

        //       return false;
        //     }
        //   }
        // }
      }
      return false;
    }
  };
}

char SProj::ID = 0;
static RegisterPass<SProj> X("sproj", "Count Dynamic Instructions Pass", false, false);