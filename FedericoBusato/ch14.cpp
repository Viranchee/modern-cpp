#include <iostream>

using namespace std;
namespace {
void debugging() {
  //
}
void assertions() {
  // Assertions slow down.
  // Never use Runtime Assertion in production
  // Static_Assert: Compile time Assert
  // Asserts can be disabled by defining NDEBUG
}
void execDebugging() {
  // -g flag: Enable debugging
  // -g3 flag: Debugging with more information
}
void memoryDebugging() {
  // _FORTIFY_SOURCE: Check buffer overflow
  // _FORTIFY_SOURCE=3
}
void hardeningTechniques() {
  //
}
void sanitizers() {
  // ASAN
  // LeakSAN
  // MemorySAN
  // UBSAN
  // ThreadSAN
}
void debuggingSummary() {
  //
}
void compilerWarnings() {
  //
}
void staticAnalysis() {
  //
}
void codeTesting() {
  // Catch2
  // Google Test
  // LLVM LIT

  // Fuzzing: LibFuzzer
}
void codeQuality() {
  // clang-tidy
}
} // namespace

void ch14() {
  cout << "ch14" << endl;
  debugging();
  assertions();
  execDebugging();
  memoryDebugging();
  hardeningTechniques();
  sanitizers();
  debuggingSummary();
  compilerWarnings();
  staticAnalysis();
  codeTesting();
  codeQuality();
}