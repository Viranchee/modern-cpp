#include <cfenv>
#include <cstdint>
#include <cstdio>
#include <functional>
#include <iostream>
#include <limits>
#include <stdio.h>
#include <sys/types.h>

using namespace std;
namespace CH3 {
void integers() {
  {

    // Model/Bits: ILP32: Windows/Unix 32-b

    // Fixed width: Always prefer over int and unsigned
    int8_t i8 = 99;
    uint8_t u8 = i8 + 10; // These are typeDefs, not real types

    // IOSTREAM takes i8 & u8 as char
    cout << "i8: " << i8 << "\tu8: " << u8 << "\tas Int: " << (int)u8 << endl;

    // size_t & ptrdiff_t are aliases data, can store biggest representable
    // value on current arch

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

  // Signed
  // If can be negative, use assertions for positive,
  // Subscripts, sizes, and indices, use signed
  // optimization (exploit undefined behavior in loops) // FIXME: I don't
  // understand this

  // Unsigned:
  // Bitmasks, Optimizations, Safety critical systems, can never be negative

  { // Query properties of types
    cout << "MaxInt: " << numeric_limits<int>::max()
         << "\tMinInt9: " << numeric_limits<int8_t>::min()
         << "\tMaxUInt8: " << numeric_limits<uint8_t>::max() << endl;
  }
  { // Promotions and Truncations
    int16_t i16 = 0xFFFF;
    int64_t i64 = i16;
    cout << "i16: " << i16 << "\ti64: " << i64 << endl;
    i64 = 0xFFFF;
    i16 = i64;
    cout << "i64: " << i64 << "\ti16: " << i16 << endl;
    i64 = 32769; // 2^15 + 1
    i16 = i64;
    cout << "i64: " << i64 << "\ti16: " << i16 << endl;
  }
  { // Undefined behaviors
    // Using unsigned and signed types together, signed multiply
    cout << "Infinite loop (failed, Clang), undefined behavior" << endl;
    for (int i = 0; i < 4; i++) {
      // cout << i * 18446744073709551610 << endl;
    }
    { // Infinite loop

      // int z = 8;
      // for (int i = z; i < INT_MAX; i += 2) {
      //   z = i;
      // }
      // cout << "z:" << z << endl;
    }

    // Detecting overflow/underflow for signed integers is hard, must be checked
    // before performing operation
  }
}

void floats() {
  { // Floats
    /*

    STD,    Precision, Sign, Exponent, Mantissa
    IEEE754 32bit:    1,      8,       23
    IEEE754 64bit:    1,     11,       52
    IEEE754 128bit:   1,     15,       112
    IEEE754 256bit:   1,     19,       236
    IEEE754 16bit:    1,      5,       10
    Google  16bit:    1,      8,       7
    E4M3:            1,      4,       3
    E5M2:            1,      5,       2
    TF32:
    Posit
    MicroScaling Formats
    Fixed point

)

    */
    double d1 = 5E3;
    d1 = 1.1e2;
    float f1 = 1.1e2;
    cout << "d1: " << d1 << "\tf1: " << f1 << endl;
    // normal or denormal:
    // If Exponent is all 0, then it's a denormal number. Interesting math here
    // Allows for more precision, but slower

    /*
      // Representations:
      // Val      Sign    Exponent    Mantissa
      // NaN      x       11111111    x
      // Inf      x       11111111    0
      // Largest  x       11111110    11111111
      // Smalles  x       00000001    00000000
      // Denormal x       00000000    x
      // 0        x       00000000    0
    */
  }
}
void floatIssues() {
  FE_ALL_EXCEPT;
  feclearexcept(FE_ALL_EXCEPT);
  auto x = 1.0 / 0.0; // compiles
  cout << "Div by 0 exception:\t" << fetestexcept(FE_DIVBYZERO) << endl;
  feclearexcept(FE_ALL_EXCEPT);
  x = 0.0 / 0.0;
  cout << "Invalid exception:\t" << (bool)fetestexcept(FE_INVALID) << endl;
  feclearexcept(FE_ALL_EXCEPT);
  x = 1e38f * 10;
  cout << "Overflow exception:\t" << (bool)fetestexcept(FE_OVERFLOW) << endl;
  feclearexcept(FE_ALL_EXCEPT);
  cout << x << endl;

  // Use relative error for comparing floats
  // For comparing, use relative_error

  // Float/Double:
  // Prefer using multiplication and division over addition and subtraction
  // Reorganize and keep near numbers with the same scale
  // If under a threshold, set to 0
  // Scaling by powers of 2 is Safe & Fast
  // Switch to log scale: Multiplication becomes addition
  // Compensation algo: Kahan summation, Dekker's fast two sum, Rump's acc sum
}

void catastrophicCancellation() {
  cout << "Integers are more Accurate than Floats for Large Numbers" << endl;
  cout << "1677217.0 from float and double to Int" << endl;
  cout << (int)1677217.0f << endl;
  cout << (int)1677217.0 << endl;

  // Case 1
  cout << "Catastrophic Cancellation: FP Increment" << endl;
  float x = 0.0f;
  for (int i = 0; i < 20'000'000; i++) {
    x += 1.0f;
  }
  cout << "x from 0.0f to 20M += 1.0f = " << x << endl;
  cout << "Catastrophic Cancellation: Ceiling Division:" << endl;
  x = std::ceil((float)20'000'001 / 2.0f);
  cout << "20M+1 / 2.0f = " << x << endl;
}
void floatComparison() {
  const float relative_error = 0.01;
  function<bool(float, float)> areFloatNearlyEqual =
      [relError = relative_error](float a, float b) {
        // Use relative error, and use max absolute for division
        // (a-b)
        if (!isfinite(a) || !isfinite(b))
          return false;
        auto diff = abs(a - b);
        auto denominator = max(abs(a), abs(b));
        auto relative_error = diff / denominator;
        return relative_error <= relError;
      };
}

} // namespace CH3
// ch3.cpp
void ch3() {
  std::cout << "Chapter 3: Basic Concepts 2" << std::endl;
  CH3::integers();
  CH3::floats();
  CH3::floatIssues();
  CH3::catastrophicCancellation();
}
