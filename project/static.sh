cd ../build
make
cd ../project
../build/bin/clang -O0 -emit-llvm -c program.cpp -o program.bc
../build/bin/opt -load ../build/lib/LLVMSProj.so -sproj < program.bc > /dev/null