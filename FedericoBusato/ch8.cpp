#import <iostream>
#include <ostream>
#include <type_traits>
#include <vector>

using namespace std;

void polymorphism() {
  // Runtime objects behave as one of derived class
  // Override: Cn be overridden in derived class
  // Overloading: static polymorphism (compile time)
  // polyorphic : overriding in C++

  // Function binding: Early / Regular: Static / Compile time binding
  // Late / Virtual: Dynamic / Runtime binding
  // Virtual function: Can be overridden in derived class

  {
    struct Base {
      virtual void overrideThisMethod() { cout << "Base\t"; }
      virtual void ifTrueBase(bool baseOrDerived) { cout << "Base\t"; }
      virtual void canNeverOveride() final { cout << "Non Virtual" << endl; }
      virtual ~Base() = default;
    } base;

    struct Derived : Base {
      void overrideThisMethod() override {
        Base::overrideThisMethod(); // Call Base class function
        cout << "Derived" << endl;
      }
      void ifTrueBase(bool baseOrDerived) override {
        if (baseOrDerived) {
          Base::ifTrueBase(baseOrDerived);
        } else
          cout << "Derived" << endl;
      }
      // void canNeverOveride() { cout << "Overridden NonVirtual" << endl; }

    } derived;

    // derived.overrideThisMethod(); // Derived
    derived.ifTrueBase(true);
    derived.ifTrueBase(false);
    derived.canNeverOveride(); // Non Virtual
  }
  // VTable Virtual Table: Function Lookup table
  // Dynamic Dispatch
  {
    // Compiler adds hidden pointer to base class which points to vtable for
    // that class

    // sizeof() considers the vtable pointer too

    // Virtual methods are not ready until constructor is completed.
    // Do not use in constructor or destructor

    // Do not use default arguments in virtual functions
  }
  // Pure Virtual Function: No implementation
  // Interface

  {
    struct Protocol {
      virtual void send() = 0;
      virtual void receive() = 0;
      virtual ~Protocol() = default;
    };
    struct TCP : Protocol {
      void send() override { cout << "TCP Send" << endl; }
      void receive() override { cout << "TCP Receive" << endl; }
    };
    struct UDP : Protocol {
      void send() override { cout << "UDP Send" << endl; }
      void receive() override { cout << "UDP Receive" << endl; }
    };
  }

  // Abstract Class: Class with pure virtual function
  {
    struct Abstract {
      Abstract() = default;           // Can have a constructor
      virtual void pureVirtual() = 0; // At least Pure Virtual Function
      virtual ~Abstract() = default;
    };
    // Abstract a; // Error: Cannot create object of abstract class
  }
}
void inheritanceAndRtti() {
  // Hierarchy: Base -> Derived1, Base -> Derived2
  /*
    Upcasting: Derived -> Base
      static_cast / dynamic_cast
      Safe, implicit or explicit
    Downcasting: Base -> Derived
      static_cast / dynamic_cast
      Unsafe, explicit
    Sidecasting: Derived1 -> Derived2
      dynamic_cast
      Unsafe, explicit
  */

  //
  { // RTTI
    // dynamic_cast : conversion of polymorphic types
    // typeid : type information (for Polymorphic classes, at least 1 virtual)
    // type_info : class, type information returned by typeid operator
    // type_info::name() : name of the type
    // type_info::operator== : compare type_info objects
  }
  // Dynamic Casting
  {
    //  Remember, T& always contains value
    // so, dynamic_cast<T&>(x) will throw exception if x is not of type T
    // dynamic_cast<T*>(x) will return nullptr if x is not of type T
  }
}
void operatorOverload() {
  struct Complex {
    float real, imag;
    Complex(float r, float i) : real(r), imag(i) {}
    Complex operator+(const Complex &i2) const {
      return Complex(real + i2.real, imag + i2.imag);
    }
    Complex operator-(const Complex &i2) const {
      return Complex(real - i2.real, imag - i2.imag);
    }
    Complex operator*(const Complex &i2) const {
      return Complex(real * i2.real - imag * i2.imag,
                     real * i2.imag + imag * i2.real);
    }
    Complex operator/(const Complex &i2) const {
      return Complex((real * i2.real + imag * i2.imag) /
                         (i2.real * i2.real + i2.imag * i2.imag),
                     (imag * i2.real - real * i2.imag) /
                         (i2.real * i2.real + i2.imag * i2.imag));
    }
    bool operator==(const Complex &i2) const {
      return real == i2.real && imag == i2.imag;
    }
    bool operator!=(const Complex &i2) const {
      return real != i2.real || imag != i2.imag;
    }

    Complex operator[](int index) const {
      if (index == 0)
        return Complex(real, 0);
      else if (index == 1)
        return Complex(imag, 0);
      else
        throw "Invalid Index";
    }

    Complex operator[](int rscale, int iscale) const {
      return Complex(real * rscale, imag * iscale);
    }

    Complex operator()() const { return Complex(-real, -imag); }
    Complex operator()(Complex &other) const { return Complex(-real, -imag); }
    // int operator()(int x) const { return x << 1; }

    // conversion
    explicit operator float() const { return real; }
    explicit operator int() const { return (int)real; }
    explicit operator bool() const { return real != 0 || imag != 0; }

    // No custom operators
    // Complex operator<|>(Complex) const { return Complex(-real, -imag); }

    // Custom operator <|>: Returns

  } n1(1, 2), n2(3, 4);

  auto n3 = n1 + n2;
  n3 = n1();
  n3 = n1(n2);

  //
}
void cppObjectLayout() {
  // Aggregate {}
  // Trivial class: supports memcpy
  // No user provided copy/move/default constructors or destructor
  // No user provided copy/move/default assignment operator
  // No virtual functions or virtual base classes
  // No brace or equal initializer for non-static members
  // All non-static members are trivial (recursively)

  // No restrictions:
  // User declared constructor different from default
  // Static members
  // Private/Protected members

  // Standard Layout Class
  // Same layout as C struct or union
  // No virtual functions or virtual base classes
  // Recursively non-static members, base and derived classes
  // Only one control acess for non-static data members
  // No base classes of same type as first non-static data member
  // No non-static data members in the most derived class, at most one base
  // class with non-static data members No base classes with non-static data
  // members

  struct StdLayout1 {
    int x;
    void y();
  };

  class StdLayout2 {
    int x, y;
    StdLayout1 z;
  };

  struct StdLayout3 {};
  struct StdLayout4 : StdLayout1, StdLayout2, StdLayout3 {};

  // POD Plain Old Data
  // std::is_pod<class Tp> // Depricated in C++20
  auto stdLayout = std::is_standard_layout<StdLayout3>::value;
  stdLayout = std::is_trivial<StdLayout3>::value;
  stdLayout = std::is_trivially_copyable<StdLayout3>::value;
  cout << "Trivially copyable stdlayout3: " << stdLayout << endl;
}

void ch8() {
  //
  polymorphism();
  inheritanceAndRtti();
  operatorOverload();
  cppObjectLayout();
}