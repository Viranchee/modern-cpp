// module my.example;
// export module my.example;
#include <iostream>

using namespace std;

// Anonymous namespace
namespace {

void includeIssues() {
  cout << "Include Issues" << endl;

  // include gaurd
  /*
  #ifndef allExposed //.h
  #define allExposed //.h
  // runFedericoChapters();
  #endif
  */
  // #pragma once: Less portable, but more efficient

  /*
  #pragma once
  #include "allExposed.h"
  #pragma endregion
  */

  // Forward Decls
  /*
  class A;
  int main() {
    A* a = new A();
    // Compiler doesn't need to know size of A, saves recompilation
  }
  */

  // Circular Dependency
  /*
  // A.h -> B.h -> C.h -> A.h
  main.cpp -> A.h

  Solution:
      Forward Declaration or
      rethinking project organization
  */

  // Common linking errors
  /*
  1. Undefined reference to `vtable for A'
      Solution:
        1. Check if right headers and sources are included
        2. Break circular deps
  2. Multiple Definitions
      Solution:
        1. Use include guards / #pragma once
        2. inline function, variable def or extern declaration
        3. Place template definition in header file and full spec in source

  */
}
void cppModules() { // C++20
  // Modules: Set of source files
  // Compiled independently of translation units that import them

  // A Module contains one or more module units
  // Contains module declaration

  // Visibility and Reachability
  // import <iostream>;

  // Modules: need to Revisit them
}

namespace ns1 {
inline namespace v1 {
void f() { cout << "v1" << endl; }
} // namespace v1
namespace v2 {
void f() { cout << "v2" << endl; }
} // namespace v2
namespace [[deprecated]] v3 {
void f() { cout << "v3" << endl; }
} // namespace v3
} // namespace ns1

void namespaces() {
  // Avoiding ambiguities
  /*
  ::f() -> global namespace
  A::f() -> A namespace
  */

  // Nexting Namespace: Less verbose syntax
  /*
  namespace ns1::ns2 { void h();}
  */

  // Namespace alias: Less verbose syntax, alternative name
  /*
  namespace some_long_name { int y;}
  namespace x = some_long_name;
  x::y;
  */

  // Unnamed/Anonymous Namespace: Internal linkage

  // Inline Namespace: Versioning
  cout << "Namespacing" << endl;
  using namespace ns1;
  v1::f();
  v2::f();
  v3::f(); // Compiler warning
  f();
}

void compilingMultipleTranslationUnits() {
  // Compiling:
  /*
  1. Naive: clang main.cpp source.cpp -o main.out
  2. Compile each translation unit in file object (compile in parallel)
      Link all object files together
      clang main.o source.o -o main.out

  Libraries:
  1. static:
      - Can not be modified without re-link final exe
      - Increases size
      + LTO
  2. dynamic (Shared lib) (DLL, .so, .dylib)
      + Can be updated without re-linking
      - Functions called outside executable
      - Linker/Compiler can't optimize code between shared libs & final exe
      * The env vars must be set to right shared lib path,
          else app crashes at beginning

  Specify lib path:
      g++/clang++ -L<libpath> main.cpp -o main.out
      LIBRARY_PATH: .a static compile time
      LD_LIBRARY_PATH: .so dynamic at runtime
  Specify lib name:
      clang++ -l<libname> main.cpp -o main.out

  Static library creation: ar

  Dynamic Library creation:
      clang++ source1.o source2.o  -shared -o libDynamic.so

  Demangling:
    Name mangling: Technique used to solve various problems caused by the need
  to resolve unique names for entities
    Transforming C++ ABI id to original source id = demangling

  c++filt
  ldd
  nm -D -C something.so w __gmon_start__ D __libc_start)main D free D malloc D
  printf
    -C: Decode low level symname
    -D: Accept a dylib

  readelf: Display info of ELF format obj files
  readelf --symbols something.so | c++filt

  objdump: Display info of obj files
  objdump -tC something.so | c++filt
    -t: Display sym, -C: Decode low level symname

  TO READ:
    1. 20 ABI breaking changes every C++ dev should know
    2. C++ policy/binary compat
    3. 10 diff b/w static & dylib



  */
}

} // namespace

void ch12() {
  cout << "Chapter 12: Address Translation" << endl;
  includeIssues();
  cppModules();
  namespaces();
  compilingMultipleTranslationUnits();
}