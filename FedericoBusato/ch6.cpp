#include <iostream>
#include <ostream>
#include <source_location>
#include <type_traits>
using namespace std;

[[deprecated("PLEASE DO NOT USE")]] [[maybe_unused]] [[noreturn]] static void
throwingFunction(int x) {
  // Throw exception, never return
  throw x;
};

static int regularDouble(int x) { return x * 2; }
[[nodiscard("Please use this return value")]] static int
noDiscardDouble(int x) {
  return x * 2;
}

static void functions() {
  /*
  Avoid code repetition
  Redability
  Organization

  Method Signature: (arguments) -> return type

  Pass by value:  + Changes to argument does not affect
                  - Performance penalty if large arguments copied
                  = Best when < 8 bytes
  Pass by Pointer:  + Object can be modified
                    + Argument not copied
                    - Null pointer, Dangling pointer
                    - Dereferencing a pointer is slower
                    = Raw arrays (use const T* or T* const)
  Pass by Reference: + Object can be modified
                     + Argument not copied
                     + Better redability than pointer
                     + References must be initialized (no null pointer)
                     + Avoids implicit conversions
                     = All cases
                     != Pass by value could give performance advantages for
                        smallObjs/built-ins which are trivially copyable

  // Pass a pointer by reference:
  void f(int* &p);
  */
  /*
  =delete : delete a function
  Helps avoid call a wrong overload

  Supports Default parameters

  */

  {}
  regularDouble(44);
  (void)noDiscardDouble(3);
  [[maybe_unused]] auto x = noDiscardDouble(3);
  cout << x << endl;
}

static void functionPointersAndObjects() {
  {
    /*
    Generic programming & composability through function pointer

    Function pointer: + No check of argument type for generic case
                      - No function inling possible

    */

    int (*f)(int) = noDiscardDouble;
    cout << f(44) << endl;

    // Signature of function pointer (Function as Argument):
    // void (*f)(int):        void f(int)
    // int (*f) (int, int):   int f(int, int)

    // Function Object: +: Type checked & safe, Inlining

    struct Doubler {
      int operator()(int x) const { return x << 1; }
    };

    auto fObj = Doubler();
    cout << fObj(100) << endl;
  }
}
static void lambda() {
  // Lambda
  // auto lambda = [capture clause] (parameters) {body}
  [[maybe_unused]] auto lambdaX2 = [](int x) { return x * 2; };
  int array[] = {1, 2, 3, 4, 5};
  auto doublerArray = [](int *arr, int size) {
    for (int i = 0; i < size; i++)
      arr[i] *= 2;
    return arr;
  };
  auto doubledArray = doublerArray(array, 5);
  for (int i = 0; i < (int)(sizeof(array) / sizeof(int)); i++)
    cout << doubledArray[i] << " ";
  cout << endl;

  /*  Capture list
  [=] : Capture all variables by value
  [&] : Capture all variables by reference
  [x, &y] : Capture x by value, y by reference
  [&, x] : Capture all variables by reference, except x by value
  [=, &x] : Capture all variables by value, except x by reference

  // Lambda can read constexpr without capturing it.

  //C++14: Parameters can be given default values
   */

  //  Lambda composition
  auto adder = [](int x, int y) { return x + y; };
  auto multiplier = [](int x, int y) { return x * y; };
  auto multiplyThenAdd = [adder, multiplier](int x, int y, int carry) {
    return adder(multiplier(x, y), carry);
  };
  cout << "Lambda chaining: 2*3+4 = " << multiplyThenAdd(2, 3, 4) << endl;

  // Lambda can be ConstEval and ConstExpr
  auto doublerConstEval = [](int x) consteval { return x * 2; };
  auto halverConstExpr = [](int x) constexpr { return x / 2; };
  cout << "ConstExprEval: " << doublerConstEval(halverConstExpr(3)) << endl;

  // Templates
  auto doubleTemplate = []<typename T>
    requires std::is_arithmetic_v<T>
  (T val) { return val * 2; };

  cout << "TemplateLambda: " << doubleTemplate(3) << endl;
  struct Random {};
  // doubleTemplate(Random{});  // Error

  // mutable Lambda expression

  int var = 1;
  auto doubleVar = [&var]() { var *= 2; };
  doubleVar();
  cout << "Captured Double: " << var << endl;
  auto setMutable5 = [var]() mutable { var = 5; };
  setMutable5();
  cout << "Mutable Passby value Global is 5?: " << var << endl;

  auto pleaseUse = [] [[nodiscard]] () { return 5; };
  (void)pleaseUse();

  class A {
    int data = 1;
    void f() {
      [[maybe_unused]] auto copyData = [data = data]() { return data; };
      [[maybe_unused]] auto copyByRef = [this]() { return data; };
      [[maybe_unused]] auto copyByValue = [*this]() { return data; };
    }
  };
  //
}
static void preprocessing() {
  //
  // MACROs are EVIL. Do Not use Macro Expansion
  /*
  Macro Expansion: - Can't be debugged, Unexpected side effects, No
  namespace/scope
  */

  // Preprocessors:
  // Any statements starting with # are preprocessor directives
  // #include , #define, #undef, #ifdef, #ifndef, #if, #else, #elif, #endif,
  // #line, #error, #pragma
  /*
  #define, #undefine

  Multi line Preprocessing: \

  Indent: #  define

  #if #else #endif

  #if defined(MACRO) == #ifdef MACRO
  #if !defined(MACRO) == #ifndef MACRO

  */

  /*
  + Define in Cpp files
  + After all includes
  + Use parenthesis
  - Hard to find compile errors
  - Macro not always evaluated
  - No Scope
  - Sideeffects

  Why use:
  Conditional Compiling
  With Assembly or other languages
  Complex name replacing
   */
  cout << "l: " << __LINE__ << " f: " << __FILE__ << " f : " << __FUNCTION__
       << " pf: " << __PRETTY_FUNCTION__ << " fnc: " << __func__
       << " s: " << __STDC__ << endl;

  auto loc = source_location::current();
  cout << "line: " << loc.line() << ":" << loc.function_name() << endl;

  // Select code based on C/C++ or Compiler or OS or Environment

  // Date and Time
  // auto dateTime = __DATE__ + __TIME__;

#if __has_include(<ctime>)
#include <ctime>
#endif

#if __cpp_lib_jthread
  cout << "C++20 jthread" << endl;
#endif

  // Macros depend on Compilers and Environment

  // #error "This is an error"
  //  #warning "This is a warning"

// #pragma message "OMG I CAN PRINT DURING COMPILE TIME"
#pragma GCC diagnostic warning "-Wformat"

#define CompileShowMessage _Pragma("message (\"OMGGG\")")

  {}
  // CompileShowMessage
}
// Token Pasting Operator

#define FUNC_GEN_A(tA, tB)                                                     \
  static void tA##tB() {}
#define FUNC_GEN_B(tA, tB)                                                     \
  static void tA##_##tB() {}

FUNC_GEN_A(my, function);
FUNC_GEN_B(my, function);

[[maybe_unused]] static void f(int) {}
[[maybe_unused]] static void f(int, int) {}
[[maybe_unused]] static void f(int, int, int) {}
[[maybe_unused]] static void f(int, int, int, int) {}
[[maybe_unused]] static void f(int, int, int, int, int) {}
#define f(...) f(__VA_ARGS__)

static void preprocessing2() {
  myfunction();
  my_function();

  // Variadics
  f(1, 2, 3, 4, 5);

  // Convert nimber literal to string, avoids runtime, compile time

#define TO_LITERAL_AUX(x) #x
#define TO_LITERA(x) TO_LITERAL_AUX(x)

  auto lol = TO_LITERA(123);
  cout << "Char123: " << lol << endl;
}

void ch6() {
  functions();
  functionPointersAndObjects();
  lambda();
  preprocessing();
  preprocessing2();
}