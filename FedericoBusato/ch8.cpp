#import <iostream>
#include <ostream>

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

  //
}
void cppObjectLayout() {
  //
}

void ch8() {
  //
  polymorphism();
  inheritanceAndRtti();
  operatorOverload();
  cppObjectLayout();
}