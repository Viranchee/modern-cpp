#include <cstdint>
#include <cstdio>
#include <iostream>
#include <stdio.h>
#include <sys/types.h>

using namespace std;

void integers() {
  // Model/Bits: ILP32: Windows/Unix 32-b

  // Fixed width: Always prefer over int and unsigned
  int8_t i8 = 99;
  uint8_t u8 = i8 + 10; // These are typeDefs, not real types

  // IOSTREAM takes i8 & u8 as char
  cout << "i8: " << i8 << "\tu8: " << u8 << "\tas Int: " << (int)u8 << endl;

  // size_t & ptrdiff_t are aliases data, can store biggest representable value
  // on current arch

  auto sizeOfSizeT = sizeof(size_t);
  auto sizeOfPtrDiffT = sizeof(ptrdiff_t);
  auto sizeOf64Int = sizeof(int64_t);
  cout << "S(size_t): " << sizeOfSizeT << "\tS(ptrdiff_t): " << sizeOfPtrDiffT
       << "\tS(int64_t): " << sizeOf64Int << endl;

  // Overflow and Wraparound
  // signed integer and unsigned integer
  // signed max positive = 2^(n-1) - 1
  i8 = 125;
  for (int j = 0; j < 10; j++) {

    printf("i8: %d\n", i8);
    i8++;
    // Detect overflow
    if (i8 < 0) {
      printf("Overflow\n");
      break;
    }
  }
  cout << endl;
}

void floats() {}
void floatIssues() {}

void ch3() {
  std::cout << "Chapter 3: Basic Concepts 2" << std::endl;
  integers();
  floats();
  floatIssues();
}
