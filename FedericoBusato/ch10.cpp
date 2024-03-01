#include <iostream>

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

void classTemplateAdvanced() {
  Alias x{3};
  //
}
void templateMetaProgramming() {}
void sfinae() {}
void variadicTemplates() {}
void cpp20Concepts() {}