#include <iostream>

using namespace std;

namespace {
void projOrg() {
  /*
  bin/
  build/
  doc/
  submodules/
  third_party/
  data/
  test/
  examples/
  utils/
  include/
  src/
  LICENSE
  README.md
  CMakeLists.txt
  Doxyfile
  .gitignore
  .clang-tidy
  .clang-format
  */

  /* Fundamental dirs
  include/
  src/
  test/
  */

  /* Empty dirs
  bin/
  build/
  doc/
  */

  /* Optional dirs
  submodules/
  third_party/
  data/
  examples/
  utils/
  cmake/
  LICENSE
  README.md
  CMakeLists.txt
  Doxyfile
  .gitignore
  .clang-tidy
  .clang-format
  */
}
void codingStyleConvention() {
  /*
  // Can do vs Should do
  // Be consistent
  // 80% lifetime cost: maintenance
  // Worst thing to code base: Size

  // My preference: LLVM coding standards
  // Use clangd + clang-format
  */
}
void hashIncludes() {
  /*
  1. Every header must be self contained.
      - Include every header you need directly
      - Don't rely on recursive includes
      - Project must compile with any include order
  2. Include as less as posible.
      - Remove unneeded headers
      - Minimize deps
      - Minimize code in headers (forward declarations)
  3. Order of #include:
      - Main module/ interface header (if any)
      - Local project
      - System includes
  4. Includes:
      - "" local headers, Absolute paths from the project include root
      - <> system headers
  5. Include Guard:
      - #ifndef-#define-#endif: Portability is strong requirement
      - #pragma once: Otherwise
      - #include IMMEDIATELY after header comment & include guard
  6. Forward declarations:
      - Prefer forward declarations: reduce compile time
      - Prefer #include: safer
  7. C++ headers, not C headers:
      - <c*> for C++ headers
      - <cmath> <cassert> <cstddef> <cinttypes> <cstdarg> <cstdbool> <cstdalign>
  <cstdbool>
  */
}
void macroPreprocessing() {
  /*
  1. Avoid defining macros, especially in headers
      - Harder to debug
  2. Use prefix for all macros, #undef macros when possible,
  */
}
void namespacing() {
  /*
  Avoid using namespace directives at global scope
  Always place code in namespace to avoid global namespace pollution
  Header: Avoid anonymous namespaces
  LLVM: Use anonymous namespace only for inline class declaration,
        static otherwise
  Content of namespaces is NOT Indented (LLVM, clang-format)
  Close namespace declarations comment (LLVM, clang-format)
  */
}
void varsAndArithTypes() {
  /*
  LLVM: Avoid static (non const) global variables
  LLVM: use fixed-width integer types?
  */
}
void functions() {
  /*
  Limit overloaded functions, prefer default args
  Smaller, logical sub-functions: Compile time & Readability
  Inline: only for small functions <10 lines
  Return Unique_Ptr instead of raw pointers
  Prefer pass by reference (except for raw arrays & built-ins)
  Pass fn args by const pointer or const reference, if not modify intent
  Prefer Enum to bool
  Clang-Tidy: Param names should be same for decl & def
  LLVM: inline comments ONLY for function definition, not declaration
  */
}
void structsAndClasses() {
  /*
  Use explicit keyword for conversion ops and constructors
  Use =delete to mark deleted functions
  Core: Mark destructor & move constructor as noexcept
  Use braced init lists for agg types
  Do not use braced init list for constructors. Can be confused with
    std::initializer_list
  {} for constructors to clearly distinguish from Function calls, and avoid
    implicit narrowing conversion

  Inheritance:
  Avoid virtual method calls in constructors
  Default args allowed only in non-virtual fn
  Polymorphic class should suppress copying
  Prefer composition over inheritance
  Avoid this
  Data first, then Function members

  */
}
void controlFlow() {
  /*
  Avoid redundant control flow.
  Merge multiple conditionals
  Avoid return true/return false pattern
  Prefer switch
  Avoid goto, do-while
  switches over enums: Do not use default labels in fully covered

  Loops:
  Early exits (continue, break, return) to simplify code
  Turn predicate loops into predicate functions
  empty() vs size() : empty() fast
  ensure all statements are reachable
  Avoid dynamic_cast (RTTI) or exceptions if possible
  Don't compare to True/False // if (x == true) -> if (x)
  Tests for null/non-null: if (ptr == nullptr) , if (count == 0)
  Do not mix signed and unsigned types
  */
}
void modernCpp() {
  /*
  static_cast reinterpret_cast const_cast dynamic_cast,
    instead of (type) c-style
  Explicit conversion for operator and constructors
  Constexpr > macro
  using > typedef
  enum class > enum
  static_assert : compile time assert
  lambda expression
  move semantic
  nullptr > NULL/0
  range-based loops > traditional for loops
  auto > explicit type
  [[depricated]] / [[noreturn]] / [[nodiscard]]
  noexcept > throw
  Always use override/final function member keyword
  Use =default constructors
  Use =delete to mark deleted functions
  */
}
void maintainability() {
  /*
  Avoid complex template programming
  Self-documenting code
  Symbolic names instead of literal values
  Type punning: Don't use reinterpretcast or union
      Use memcpy or bit_cast
  Enforce const-correctness
      Pass by const value: useless copy, abi break
      const return: useless copy
      const data member: disable assignment & copy const
      const local vars: verbose, rarely effective

  Don't overload operators with special semantics &&, ^
  [LLVM] Use assert to document preconditions and assumptions
  Address compiler warnings
  prefer sizeof(variable/value) to sizeof(type)
  Prefer core language features: char vs std::byte
  */
}
void naming() {
  /*
  Whole words, instead of tmp
  avoid short & very long names
  Length: proportional to size of the scope it contains
  Reserved names: use _var or _VAR
  Common loop var names: i, j, k, l
      it: iterators
  bool: is/has/should/does/can verbs start
  Use set prefix for modifier methods
  Do not use get for observer methods (const) without params. eg. size()

  */
}
void readabilityAndFormatting() {
  /*
  LLVM:
  Line length: 80
  tab: 4 spaces


  */
}
void codeDoc() {
  //
}
} // namespace
void ch13() {
  cout << "Chapter 13" << endl;
  projOrg();
  codingStyleConvention();
  hashIncludes();
  macroPreprocessing();
  namespacing();
  varsAndArithTypes();
  functions();
  structsAndClasses();
  controlFlow();
  modernCpp();
  maintainability();
  naming();
  readabilityAndFormatting();
  codeDoc();
}