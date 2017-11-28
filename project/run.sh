clear
cd ../build
make
cd ../project
../build/bin/clang -O0 -emit-llvm -c program.cpp -o program.bc
../build/bin/opt -load ../build/lib/LLVMSProj.so -sproj < program.bc > instrumented.bc
cd ../instrumentation
../build/bin/clang -std=c++11 -O0 -emit-llvm -c dynamic.cpp -o dynamic.bc
../build/bin/llvm-link ../project/instrumented.bc dynamic.bc -o instrumented.linked.bc
../build/bin/llc -filetype=obj instrumented.linked.bc -o=instrumented.o
g++ -std=c++11 instrumented.o $LLVMLIBS $LDFLAGS -o instrumented.exe
./instrumented.exe
cd ../project