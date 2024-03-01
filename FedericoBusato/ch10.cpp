#include <csetjmp>
#include <iostream>
#include <string>

using namespace std;

static void classTemplate();
static void classTemplateAdvanced();
static void templateMetaProgramming();
static void sfinae();
static void variadicTemplates();
static void cpp20Concepts();

void ch10() {
  cout << "Templates & Meta programming 2" << endl;
  classTemplate();
  classTemplateAdvanced();
  templateMetaProgramming();
  sfinae();
  variadicTemplates();
  cpp20Concepts();
}

template <typename T> struct typenameTemplate {
  T a;
};
template <int N1> struct numericTemplate {
  int n = N1;
};

template <typename T, typename R> struct GenericT {}; // Generic class template
template <typename T> struct GenericT<T, int> {};     // Partial specialization
template <> struct GenericT<int, float> {};           // Full specialization

template <typename T, typename R> struct is_same {
  static constexpr bool value = false;
};
template <typename T> struct is_same {
  static constexpr bool value = true;
};

#include <type_traits>

template <typename T> struct isConstPointer : std::false_type {};
template <typename R> struct isConstPointer<const R *> : std::true_type {};

// Compare class templates
template <typename T> struct A {};

template <typename T, typename R> struct Compare : std::false_type {};
template <typename T, typename R>
struct Compare<A<T>, A<R>> : std::true_type {};

static void classTemplate() {
  //
}

// Deduction guide

template <typename T> struct Origin {
  Origin(T) {}
};

template <typename T> Origin(T) -> Origin<int>; // Deduction guide

template <typename T> using Alias = Origin<T>; // alias template

// User defined deduction guide
template <typename T> struct MyString {
  MyString(T) {}
  MyString myFunc() { return MyString("abc"); }
};

MyString(const char *) -> MyString<std::string>; // deduction guide
MyString<const char *> customstr{"abc"}; // construct 'MyString<const char*>'
// customstr.myFunc(); // Doesn't work in class scope

// Solution: Use a Factory helper
template <typename T> auto makeMyString(T &t) { return MyString(t); }

//
template <typename T, typename R> struct TemplatedClass {
  template <typename X, typename Y> void templatedFunction();
};

// Generic + Generic
template <typename T, typename R>
template <typename X, typename Y>
void TemplatedClass<T, R>::templatedFunction() {}

// Full class specialization + Generic function
template <>
template <typename X, typename Y>
void TemplatedClass<int, float>::templatedFunction() {}

// Full Specialization
template <>
template <>
void TemplatedClass<int, float>::templatedFunction<int, float>() {}

// Structure Templates
template <typename T> struct StructTemplate {
  using type = int;
};
template <typename R> void someFunc() {
  using Type = typename StructTemplate<R>::type;
  [[maybe_unused]] Type x;
}
// Simplifying:
template <typename T> using STType = typename StructTemplate<T>::type;
template <typename T> void workOnType() {
  using Type = STType<T>;
  [[maybe_unused]] Type x;
}

template <typename T> struct THierarchy {
  T x;
  void f() {}
};
template <typename T> struct B : THierarchy<T> {
  using THierarchy<T>::x; // needed (otherwise it could be another
                          // specialization)
  using THierarchy<T>::f; // needed
  void g() {
    x; // without 'using': this->x f();
  }
};

template <typename T> struct TSingleType {};
template <typename T, typename R> struct TMultiTypes {};
template <typename T> void f() {}
//----------------------------------------------------------------------------------
class C {
  friend void f<int>();                          // match only f<int>
  template <typename T> friend void f();         // match all f templates
  friend struct TSingleType<int>;                // match only A<int>
  template <typename> friend struct TSingleType; // match all A templates
  template <typename, typename>
  friend struct TMultiTypes; // match all A templates
public:
  int x;

  // template <typename T, int> friend struct TMultiTypes<int, T>;
  // partial specialization cannot be declared as a friend
};

template <typename T> struct TTemplateParameter;
template <template <typename> typename A> struct TTemplateParameters {
  struct X {
    A<int> intt;
    A<float> flt;
  };
};

static void classTemplateAdvanced() {
  customstr.myFunc();        // Works
  makeMyString("Some word"); // Works
  //  Alias x{3};

  { // Class Template Advanced
    /*
    Given a templated class with templated function

    Specialization types:
    Generic + Generic
    Full + Generic/Full
    */

    //

    [[maybe_unused]] TemplatedClass<float, float> obj;
    // obj.templatedFunction<int, int>(); // Might not compile with older C++
    /*
        Template Hierarchy: Need to specify Template Type for the base class
    whenever you have a derived class.
    */
  }

  { // Structure Templates
    someFunc<int>();
    workOnType<int>();
  }
  { // Template H

    /*
    Virtual functions:
    Cannot have template arguments

    Templates are compile time feature
    Virtual functions are runtime feature
    */
  }

  { // Friend and Templates
  }
  { // Template Template parameters
  }
}

// Factorial at compile time (and at runtime)
template <int N> struct Factorial {
  static constexpr int value = N * Factorial<N - 1>::value;
};
template <> struct Factorial<0> {
  static constexpr int value = 1;
};

template <typename T> int factorial(T value) {
  T tmp = 1;
  for (int i = 1; i <= value; i++)
    tmp *= i;
  return tmp;
}

void templateMetaProgramming() {
  [[maybe_unused]] constexpr int fact5 = Factorial<5>::value;
  // Compile time feature
}
void sfinae() {
  // SOME MESS I AM NOT GOING INTO
  // SFINAE: Substitution Failure Is Not An Error
  // Simply restrict the template instantiation
}

// Variadic add example:

// Base case
template <typename T, typename R> auto add(T t, R r) { return t + r; }
template <typename T, typename... TArgs> auto add(T a, TArgs... args) {
  return a + add(args...);
}

template <typename T> struct GetArity;
// generic function pointer
template <typename R, typename... Args> struct GetArity<R (*)(Args...)> {
  static constexpr int value = sizeof...(Args);
};
// generic function reference
template <typename R, typename... Args> struct GetArity<R (&)(Args...)> {
  static constexpr int value = sizeof...(Args);
};
// generic function object
template <typename R, typename... Args> struct GetArity<R(Args...)> {
  static constexpr int value = sizeof...(Args);
};

void threeParamFunction(int, char, double) {}
void variadicTemplates() {
  // Variadics should be last in the declaration.
  // For total variadics, use sizeof...(args) operator
  [[maybe_unused]] auto res = add(1.0f, 2, 3, 4, 5);

  // Can use pass by value, ref and pointer

  // Can fold

  // Recursive data structures

  // Arity
  static_assert(GetArity<decltype(threeParamFunction)>::value == 3);
  auto &ref = threeParamFunction;
  static_assert(GetArity<decltype(ref)>::value == 3);
  auto *ptr = threeParamFunction;
  static_assert(GetArity<decltype(ptr)>::value == 3);
  static_assert(GetArity<decltype(add<int, float, double>)>::value == 3);
}

// Add only int types using cpp 20 concepts
template <typename T>
concept Arithmetic = std::is_arithmetic_v<T>;

template <Arithmetic T> T addUsingConcept(T a, T b) { return a + b; }

template <Arithmetic T>
auto addUsingAutoConcept(Arithmetic auto a, Arithmetic auto b) {
  return a + b;
}

// After template
template <typename T>
  requires Arithmetic<T>
auto addUsingRequires(T a, T b) {
  return a + b;
}

// After function declaration
template <typename T>
auto addUsingRequires(T a, T b)
  requires(sizeof(T) == 4)
{
  return a + b;
}

static void cpp20Concepts() {
  // Extension for templates.

  // Concepts are a way to restrict the template instantiation
  // Better than SFINAE

  // Easy R/W and understand
  // Clear compile time messages for debugging
  // Fast compile time

  // Keywords: requires, concept, requires clause
  //

  // requires: Acts like SFINAE

  // Multiple concepts and requirements,
  // multiple can be joined using '&&' or '||'
  // C & R Can be used together

  // Similar to where clause in Swift

  // Nested requires
}