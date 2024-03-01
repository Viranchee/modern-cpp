#include <cassert>
#include <cstdint>
#include <iostream>
#include <variant>

using namespace std;

void entities() {
  // Entity: value, object, ref, fn, enum, type, class member, template,
  // namespace
}

// 2 Declarations
static void declAndDef();
static void declAndDef();

// Definition
static void declAndDef() {
  // 1 definition, multiple declarations
  // eg. Function declaration and definition
  // Declaration's comments prioritized over definition's comments
}
static void enums() {
  enum Color { RED, GREEN, BLUE };
  Color c = RED;
  cout << "Value of Red: \t" << c << endl;          // 0
  cout << "Value is Red: \t" << (c == RED) << endl; // 0
  enum Fruit { APPLE, BANANA, ORANGE };
  Fruit f = APPLE;
  auto enumCompareResult = (static_cast<Fruit>(c) == static_cast<Fruit>(f));
  cout << "RED is Apple: \t" << enumCompareResult << endl; // 1

  // enum class
  enum class Color2 { RED, GREEN, BLUE };
  enum class Fruit2 { APPLE, BANANA, ORANGE };

  Color2 c2 = Color2::RED;
  Fruit2 f2 = Fruit2::APPLE;
  // cout << "RED is Apple: \t" << (c2 == f2) << endl; // Error
  cout << "(int) RED == Apple: \t" << (bool)((int)c2 == (int)f2) << endl;
  //  Set type
  enum class Color3 : char { RED, GREEN, BLUE };
  enum class Fruit3 : int8_t { APPLE, BANANA, ORANGE };

  // Deprecated
  // enum class Color4 { RED4, GREEN4, [[deprecated]] BLUE4 };
  // Color4 obj = Color4::BLUE4;

  switch (c) { // C++ 20
    using enum Color;
  case RED:
    cout << "Red" << endl;
    break;
  case GREEN:
    cout << "Green" << endl;
    break;
  case BLUE:
    cout << "Blue" << endl;
    break;
  }

  Color2 c2_1;
  c2_1 = Color2::GREEN;
  // consume c2_1 as a noop
  (void)c2_1;

  // Fruit3 value = (int8_t)33;
  // Color3 c33 = 'a';
  Fruit3 value = (Fruit3)33;
  Color3 c33 = (Color3)'a';
  (void)value, (void)c33;
}
static void structs() {
  { // Structs and Enums inside structs

    struct A {
      int a;
      char b;
    } a, b;
    a.a = 1;
    a.b = 'a';
    b.a = 2;
    b.b = 'b';

    // Enums in Structs

    struct B {
      enum class Color { RED, GREEN, BLUE };
      Color c;
    } b1, b2;
    (void)b1, (void)b2;
    auto y = B::Color::BLUE;
    cout << "Color enum value: " << (int)y << endl;

    struct C {
      enum { NONAME_1 = 255, NONAME_2 };
    };
    auto x = C::NONAME_1;
    cout << "Noname enum value: " << x << endl;
  }
  { // Unnamed struct
    struct {
      int a;
      char b;
    } a, b;
    a.a = 1;
    a.b = 'a';
    b.a = 2;
    b.b = 'b';
    (void)a, (void)b;

    // Anonymous struct
    struct {
      int topLevel;
      struct {
        int value;
      } nested;
    } nestedEg;
    nestedEg.topLevel = 1;
    nestedEg.nested.value = 2;
  }

  { // Bitfield
    struct BitField {
      int i8 : 8;
      int i10 : 10;
      int i1 : 1;
      int : 0; // reset: force the next field
      int i32 : 32;
      // int i32_2 : 32;
    } bitfieldInstance;

#define i8_CONST 0b1010101
    bitfieldInstance.i8 = i8_CONST;
    bitfieldInstance.i1 = 0;

    for (int i = 0; i < 4096; i++) {
      bitfieldInstance.i10 = i;
      if (bitfieldInstance.i8 != i8_CONST) {
        cout << "#i8 changed: " << bitfieldInstance.i8 << endl;
      }
      if (bitfieldInstance.i1 != 0) {
        cout << "#i1 changed: " << bitfieldInstance.i1 << endl;
      }
    }
    cout << endl;

    // Print the whole struct bitfieldInstance's memory contents
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wbitfield-constant-conversion"
    bitfieldInstance.i10 = 0xFFFF;
#pragma GCC diagnostic pop
    cout << "i10: " << bitfieldInstance.i10 << endl;
    bitfieldInstance.i1 += 1;
    bitfieldInstance.i1 += 101;
    cout << "i1: " << bitfieldInstance.i1 << endl;
    // cout << bitfieldInstance << endl;
  }
}

static void unions() {
  union A {
    int a;
    char b;
  } eg;
  eg.a = 1023; // 0x3FF
  eg.b = 0;    // 0x00
  // The bits 0x3xx still stay set in the memory
  cout << "Union: " << eg.a << endl;

  // Std::variant is a type-safe union
  std::variant<int, float, std::string> v;
  v = 33;
  cout << "t:" << v.index() << "\tval: " << std::get<int>(v) << endl;
  v = 0.5f;
  cout << "t:" << v.index() << "\tval: " << std::get<float>(v) << endl;
  v = "Hello";
  cout << "t:" << v.index() << "\tval: " << std::get<std::string>(v) << endl;

  // check type of variant
}

static void produceError() {
  assert(1 == 0);
  [[maybe_unused]] int arr[] = {1, 2, 3, 4, 5};
}

static void controlFlow() {
  // Short circuiting
  if (true || (produceError(), false)) {
    cout << "Short circuiting" << endl;
  }

  struct A {
    int x;
    int y;
  };
  A array[] = {{1, 2}, {5, 6}, {7, 1}};
  for (auto [x1, y1] : array)
    cout << x1 << "," << y1 << " "; // print:1,2 5,6 7,1

  cout << endl;
  cout << "Switch fallthrough" << endl;
  char x = 'a';
  switch (x) {
  case 'a':
    cout << "a" << endl;
    [[fallthrough]];
  case 'b':
    cout << "b" << endl;
    break;
  default:
    cout << "default" << endl;
  }

  if (int ret = 1000; ret < 10) {
    cout << "ret<10: " << ret << endl;
  } else {
    cout << "ret>10: " << ret << endl;
  }
  { // Switch initializer
    // i scope limited to the Switch statement
    auto x = 50;
    switch (auto i = 5; x) {
    case 1:
      cout << "1" << endl;
      break;
    case 5:
      cout << "5" << endl;
      break;
    case 50:
      cout << "50" << endl;
      break;
    default:
      cout << "default" << i << " " << x << endl;
    }

    for (int i = 0; auto x : {'a', 'b', 'c'}) {
      cout << i++ << ":" << x << " "
           << "\t";
    }
    cout << endl;
  }

  [[maybe_unused]] int x1 = 0;
}

template <typename T> int template1SizeOfT(T value) {
  auto x = 5;
  if constexpr (sizeof(value) >= 4) {
    x = 4;
  } else {
    x = 2;
  }
  x = sizeof(value);
  return x;
}
template <typename T> int template2DeclType(T value) {
  using R = decltype(value);
  return R{};
}

// This comment is from ch4.cpp
void ch4() {
  cout << "Chapter 4: Basic Concepts 3" << endl;
  // Entities and Control Flow
  // entities();
  // declAndDef();
  // enums();
  // structs();
  // unions();
  controlFlow();
  declAndDef();
  enums();
  structs();
  unions();

  // Templates
  cout << "Template" << endl;
  cout << "sizeOf(Int)\t" << template1SizeOfT(1) << endl;
  cout << "sizeOf(Float)\t" << template1SizeOfT(1.0f) << endl;
  struct {
    int x;
    float y;
    std::string z;
  } a;
  cout << "sizeOf(UnnamedStruct)\t" << template1SizeOfT(a) << endl;

  // Decltype
  cout << "Decltype" << endl;
  cout << "Decltype(Int)\t" << template2DeclType(1) << endl;
  cout << "Decltype(Float)\t" << template2DeclType(1.0f) << endl;
  // cout << "Decltype(UnnamedStruct)" << template2DeclType(a) << endl; // ERROR
}