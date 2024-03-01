#import <iostream>
#include <ostream>
#include <type_traits>

using namespace std;

void fnTemplate();
void templateVariableParameterTypes();
void compileTimeUtils();
void typeTraits();

// Generics: Templates and Metaprogramming
void ch9() {
  fnTemplate();
  templateVariableParameterTypes();
  compileTimeUtils();
  typeTraits();
}
void fnTemplate() {
  // Pros:
  // Functions, Classes, Variables
  // Generic programming & Performance

  // Cons:
  // Redability
  // Compile time / binary size increase

  // Implicit
  // CodeGen on deduced argument types or explicit template arguments.
  // Only when definition is needed

  // Explicit
  // CodeGen on explicit template arguments specified in declaration.
  // Useful when dealing with multiple translation units to reduce binary size
}
template <typename T> void aTemplateFn(T a) {}
void aTemplateUser() {
  aTemplateFn(3);        // generates f(int) -> Implicit
  aTemplateFn<short>(3); // generates f(short) -> Implicit
}

template void aTemplateFn(
    int); // generates f(int) -> Explicit; useful for reducing binary size

void templateVariableParameterTypes() {
  // template parameter: generic type or NTTP (eg. int, enum, etc.)
}

enum class MyEnum { A, B, C };
template <MyEnum E> void aTemplateFn() {}

// Template Parameter Can have default values
template <typename T = int> void someTemplateFn(T a) {}
template <int x = 5> int addWith(int val) { return val + x; }

// Template parameter init
template <typename T, int S = sizeof(T)> void aTemplateFn(T a) {
  T *newT;
  newT = new T[S];
}

// Template Function overloading, Template overloading

// Template specialization
template <typename T> bool compare(T a, T b) { return a < b; }
// A better float point implementation
template <> bool compare<float>(float a, float b) { return a - b < 1e-6; };

// Specialization: IF ALL template arguments are specialized

// Template variable
template <typename T> constexpr T pi = T(3.1415926535897932385L);

template <typename T> T circularArea(T r) { return pi<T> * r * r; }

void _callCircularArea() {
  auto res = circularArea(3.3f); // Float
  cout << "Area: " << res << endl;
  circularArea(3.3); // Double
  cout << "Int area: " << circularArea(3)
       << endl; // Compile error, narrow conversion
}
// circularArea(3.0f); // 28.2743

//  Template parameter types
/*
Int, Enum, Float, Auto, class literals & concepts, generic typename

Rarely: function, ref//pointer to global static fn/object, pointer to member,
nullptr
*/

// Type traits
using adder = void(int, int);      // Function type
using adder2 = void (*)(int, int); // Function pointer

template <typename T, int Size> struct VECTOR {};
template <int Size> using Bitset = VECTOR<bool, Size>; // partial specialization
using IntV4 = VECTOR<int, 4>;                          // full specialization
using fn = decltype(compileTimeUtils);

void compileTimeUtils() {
  _callCircularArea();

  static_assert(2 + 2 == 4, "2+2 != 4"); // Compile time assert
  static_assert(sizeof(int) == sizeof(int[1]), "Works");

  // Get types
  int a = 3;
  decltype(a) d1 = 5;
  [[maybe_unused]] decltype((a)) d2 = d1; // Should be int&
}
void typeTraits() {

  // Introspection: inspect & query type & properties
  // Reflection: examine, introspect, modify it's own structure & behavior

  // Compile time introspection & reflection
  // Type traits:
  // std::is_integral, std::is_floating_point, std::is_pointer,

  /*

  is_integral
  is_floating_point
  is_arithmetic
  is_signed, is_unsigned
  is_enum
  is_void
  is_pointer
  is_null_pointer

  is_array, is_reference, if_function
  is_class, is_abstract, is_polymporphic
  is_const
  is_same / is_base_of / is_convertible
*/

  // std::make_signed, std::make_unsigned
  // remove_pointer<class Tp>
  // remove_reference<class Tp>
  // add_pointer<class Tp>
  // add_lvalue_reference<class Tp>
  // add_rvalue_reference<class Tp>
  // conditional<bool Bp, class If, class Then>
  // decay<class Tp> // Same type as function parameter passed by-value
  // remove_cv<class Tp>; // remove const and volatile
  // add_const<class Tp> // add const
}

template <typename T> T integral_div(T a, T b) {
  static_assert(std::is_integral<T>::value, "T must be integral");
  return a / b;
}