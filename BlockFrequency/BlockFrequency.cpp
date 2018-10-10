#include "llvm/IR/Function.h"
#include "llvm/Pass.h"
#include "llvm/Support/raw_ostream.h"  //Similar to iostream
#include "llvm/Analysis/BlockFrequencyInfo.h"


using namespace llvm;

namespace{
 struct MyBlockFrequency : public FunctionPass{
  static char ID;
  MyBlockFrequency() : FunctionPass(ID){}
  void getAnalysisUsage(AnalysisUsage &AU) const override {
   AU.setPreservesCFG();
   AU.addRequired<BlockFrequencyInfoWrapperPass>();
  }
  bool runOnFunction(Function &F)override{ 
   BlockFrequencyInfo &BFI = getAnalysis<BlockFrequencyInfoWrapperPass>().getBFI(); 
   unsigned int basicblockcount = 0;
   for(BasicBlock &BB : F){
    basicblockcount++;
     BFI.getBlockFreq(&BB);
     BFI.printBlockFreq(errs(), &BB);
     errs() << "\n";
    }
   errs() <<"Blocos Analizados: " <<  basicblockcount << "\n";
   return false;
  }
 };
}

char MyBlockFrequency::ID = 0;
static RegisterPass<MyBlockFrequency> X("myblockfrequency", "My own BlockFrequencyInfo pass", false, false);
