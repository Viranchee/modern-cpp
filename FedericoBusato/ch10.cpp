#include <iostream>
#include <string>

using namespace std;

void classTemplate();
void classTemplateAdvanced();
void templateMetaProgramming();
void sfinae();
void variadicTemplates();
void cpp20Concepts();

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

void classTemplate() {
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
  Type x;
}
// Simplifying:
template <typename T> using STType = typename StructTemplate<T>::type;
template <typename T> void workOnType() {
  using Type = STType<T>;
  Type x;
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

void classTemplateAdvanced() {
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
void templateMetaProgramming() {}
void sfinae() {}
void variadicTemplates() {}
void cpp20Concepts() {}