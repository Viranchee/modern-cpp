#include <iostream>
#include <ostream>
using namespace std;

[[deprecated("PLEASE DO NOT USE")]] [[noreturn]] void throwingFunction(int x) {
  // Throw exception, never return
  throw x;
};

int regularDouble(int x) { return x * 2; }
[[nodiscard("Please use this return value")]] int noDiscardDouble(int x) {
  return x * 2;
}

void functions() {
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

void functionPointersAndObjects() {
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
void lambda() {
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
  for (int i = 0; i < sizeof(array) / sizeof(int); i++)
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

  //
}
void preprocessing() {}
void ch6() {
  functions();
  functionPointersAndObjects();
  lambda();
  preprocessing();
}