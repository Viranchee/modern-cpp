#include <cmath>
#include <iostream>
using namespace std;

static void raii() {
  // Holding a resource is a class invariant, and is tied to object lifetime
}
static void classes() {
  struct Struct {
    int x;
    void f() {} // Inline definition
  };
  class Class {
    [[maybe_unused]] int x;
    void f() {} // Function member, Out of line definition
  };
}
static void hierarchyAndAccessSpecifiers() {
  // Derived class can extend Parent class
  class ParentClass {
  public:
    int x;
  };
  class ParentPublicClass {
  public:
    int theoryOfEverything = 42;
  };
  class DerivedClass : public ParentPublicClass, private ParentClass {};

  DerivedClass dObj;
  // dObj.x;                  // Error: x is private
  (void)dObj.theoryOfEverything; // OK: theoryOfEverything is public

  struct BaseStruct {
    int base = 69;
    // protected: Function members and deried classes access
  protected:
    int protectedBase = 42;
  };
  struct DerivedStruct : BaseStruct {
    int derived = 42;
    int getProtected() { return protectedBase; }
  };
  DerivedStruct dStruct;
  cout << "Base and Derived struct values: " << dStruct.base << " "
       << dStruct.derived << " " << dStruct.getProtected() << endl;

  //  Struct: public default
  //  Class: private default

  // Can Control public protected and private visibility to the user
}
static void constructors() {
  // Initialize all data members.
  // Multiple constructors with different signatures
  // Can be constexpr

  // Implicit Default constructor is Marked Deleted, IF:
  // 1. User defined constructor
  // 2. Non static member/base class of ref/const type
  // 3. Non static member/base class which has deleted / inaccessible default
  // constructor
  // 4. Non static member/base class with deleted/inaccessible destructor

  struct NoDefault1 {
    NoDefault1(int) {}
  };
  // NoDefault1 nd1; // Error: NoDefault1 has no default constructor
  struct NoDefault2 {
    int &x;
    const int y;
  };
  // NoDefault2 nd2; // Error: NoDefault2 has no default constructor

  struct NoDefault3 {
    NoDefault2 var;
  };
  // NoDefault3 nd3; // Error: NoDefault2 has no default constructor

  struct NoDefault4 {
    NoDefault4() = delete;
  };
  // NoDefault4 nd4; // Error: NoDefault4 has a deleted default constructor
  struct NoDefault5 {
  private:
    ~NoDefault5() {}
  };
  // NoDefault5 nd5; // Error: NoDefault5 has a private destructor

  // Initializer list
  struct InitializerList {
    int x, y;
    // int &z; // Error: Reference must be initialized
    const char *str = nullptr;
    InitializerList(int x1) : x(1) {}
    InitializerList(int x1, int y1) : x(x1), y(y1) {}

    InitializerList() {}
    InitializerList(const char *str1) : str{str1} {}

    // const and ref data MUST be init with initializer list or BRACE/Equal init
    // syntax
  };

  struct InitList2 {
    int x;
    const char y;   // MUST be initialized
    int &z;         // MUST be initialized
    int &v = x;     // Equal init
    const int w{4}; // Brace init

    InitList2() : y('a'), z(x) {}
    // InitList2() : x(3), y('z'), z(x) {} // Cannot be redeclared
  };

  // Initialization follows ORDER OF DECLARATION, not order of initialization

  struct ArrayWrap {
    int *arr, size;

    // ArrayWrap(int usize) : size{usize}, arr{new int[size]} {} // COMMON ERROR
    ArrayWrap(int usize) : arr{new int[usize]}, size{usize} {} // FIXED
  };

  // Uniform Init

  // Most vexing parse problem

  struct A {};
  struct B {
    B(A a) {}
    void f() {}
  };
  B b((A())); // Function declaration
  // b.f();    // Error: b is a function

  // Constructors and Inheritance
  // First, base constructors are called, then derived constructors
  // Same as in Swift

  // Delegate Constructor

  struct SomeStruct {
    int a;
    float b;

    SomeStruct(int a1, float b1) : a(a1), b(b1) {
      cout << "Regular Init" << endl;
    }
    // delegate constructor
    SomeStruct(int a1) : SomeStruct(a1, 0.0f) {}
    SomeStruct(float b1) : SomeStruct(0, b1) {}
    SomeStruct() : SomeStruct(0) {}
  };
  // explicit Keyword
  // Prevents implicit conversion

  struct ExplicitExample {
    explicit ExplicitExample() {}
    explicit ExplicitExample(int) {}
    explicit ExplicitExample(int, int) {}
    explicit ExplicitExample(int, int, int) {}
  };
  // ExplicitExample e = 42; // Error: No implicit conversion
  ExplicitExample e1(42);   // OK
  ExplicitExample e1_1{42}; // OK
  // ExplicitExample e2 = {42, 42}; // Error: No implicit conversion
  ExplicitExample e3{42, 42};                 // OK
  ExplicitExample e4{42, 42, 42};             // OK
  ExplicitExample e5 = (ExplicitExample)(42); // OK
  e5 = (ExplicitExample){42};                 // OK
  e5 = (ExplicitExample){42, 42, 42};         // OK

  // NoDiscard Constructor
  struct NoDiscard {
    [[nodiscard("Please use this")]] NoDiscard() {}
  };

  // Call explicit constructor
}
static void copyConstructors() {
  //
  struct AStruct {
    int x;
    AStruct() {}                     // default constructor
    AStruct(int x1) {}               // non default constructor
    AStruct(const AStruct &other) {} // Copy Constructor
  };
  //
}
static void destructor() {
  // Releases resources
  // 1 Destructor.
  // C++20: constexpr allowed
  struct Array {
    int *array;
    Array(int size) : array{new int[size]} {}
    ~Array() { delete[] array; }
  };
  // Never Inherited.
  // Destruction order: current class -> parent class
  // Reverse of construction order

  // Default constructor / destruct

  struct SomeStruct {
    int x;

  public:
    SomeStruct() = default;
    ~SomeStruct() = default;

    SomeStruct(int x1) : x{x1} {}
    SomeStruct(const SomeStruct &other) = default;
    SomeStruct &operator=(const SomeStruct &other) = default;

    static int someStatic() { return 42; }
    // static const int sCons = 42; // Not allowed in local scope
    static constexpr int sConsFunc() { return 42; }
    // static int sCons;// = 42;
  };
  //
}

struct TryStatic {
  static int x; // = 5 // Can't init value
  static int f() { return x; };
  static int &g() { return x; };
};
static void defaultedConstructursDestructursOperators() {}

static void keywords() {

  // Const and Mutable
  {
    struct ConstEg {
      int x = 5;
      const int EVE = 42;
      mutable int variable = 0;

      int observer() const { return x; }
      int inspector() const { return variable; } // R
      int &observer() { return variable; }       // Overload: Allows R/W
    } const c;
    // c.EVE = 42; // Error: EVE is const
    // c.x = 100; // Error: x is const
    c.variable = 42;
    // c.observer() = 42; // Doesnt work on const
  }
  // Changing inheritance attributes: using
  {

    struct A {
    protected:
      int protectedMember = 3;
    };
    struct B : A {
    public:
      using A::protectedMember;
    } b;

    b.protectedMember = 42; // OK: protectedMember is public in B
  }
  {}
}

// Friend class and Friend method
// Not symmetric, not transitive, not inherited
struct A {
  friend struct B;
  friend int friendMethod(A a);
  A(const A &) = delete;
  A(int x1) : x{x1} {}

private:
  int x;
};

int friendMethod(A a) { return a.x; }

struct B {
  int f(A a) { return a.x; }
};

// Delete keyword

void ch7() {
  cout << "Chapter 7: Object Oriented Programming" << endl;
  raii();
  classes();
  hierarchyAndAccessSpecifiers();
  constructors();
  copyConstructors();
  destructor();
  defaultedConstructursDestructursOperators();
  keywords();
  //
  A(42);
}