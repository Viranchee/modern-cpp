#include <csetjmp>
#include <cstdint>
#include <iostream>
// Disable individual flags, eg -Wdeprecated-enum-compare
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"

using namespace std;

void entities() {
  // Entity: value, object, ref, fn, enum, type, class member, template,
  // namespace
}

// 2 Declarations
void declAndDef();
void declAndDef();

// Definition
void declAndDef() {
  // 1 definition, multiple declarations
  // eg. Function declaration and definition
  // Declaration's comments prioritized over definition's comments
}
void enums() {
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
void structs() {
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

    bitfieldInstance.i8 = 0xFF;
    cout << "i8: " << bitfieldInstance.i8 << endl;
    bitfieldInstance.i10 = 0xFFFF;
    cout << "i10: " << bitfieldInstance.i10 << endl;
    bitfieldInstance.i1 += 1;
    bitfieldInstance.i1 += 101;
    cout << "i1: " << bitfieldInstance.i1 << endl;
    // cout << bitfieldInstance << endl;
  }
}

void controlFlow() {}

// This comment is from ch4.cpp
void ch4() {
  cout << "Chapter 4: Basic Concepts 3" << endl;
  // Entities and Control Flow
  entities();
  declAndDef();
  enums();
  structs();
  controlFlow();
}