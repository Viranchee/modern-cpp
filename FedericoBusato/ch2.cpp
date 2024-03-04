
#include <compare>
#include <cstdint>
#include <cstdio>
#include <iostream>
#include <stdio.h>
#include <utility>

namespace CH2 {

void pointerToAPointer() {
  int *val = nullptr;
  auto size = sizeof(int);
  val = (int *)malloc(size);
  *val = 500;
  *val = true ? 500 : (int)NULL;
  std::cout << "Value: " << val << "\tDeref " << &val << "\tRef " << *val
            << std::endl;
  // Make pointer to a pointer
  int **ptr = &val;
  std::cout << "Pointer: " << ptr << "\tDeref " << *ptr << "\tRef " << **ptr
            << std::endl;
  // Free the memory
  free(val);
}

void promotions() {
  // Promotions
  uint8_t c = 'a';
  auto x = -c;
  x = -c;
  x = +c;
  std::cout << "Promotion: " << x << std::endl;
  std::cout << "+x: " << +x << std::endl;
}

auto doubleValue(int x) { return x * 2; }                 // C++ 17
void printAuto(auto x) { std::cout << (x) << std::endl; } // C++ 20

void implicitPromotion() {
  // Implicit promotion
  char a = '0';
  std::cout << "a: " << a << std::endl;
  std::cout << "+a: " << +a << std::endl;
  std::cout << "a+0: " << (a + 0) << std::endl;
  std::cout << "a+a: " << (a + a) << std::endl;
}

int get100() {
  ;
  std::cout << "Extra operation, return 100" << std::endl;
  return 100;
}
void commaOperator() {
  int i = (get100(), -100);
  std::cout << "Comma operator: " << i << std::endl;
}

void printSpaceshipResult(std::string str, std::strong_ordering cmp) {
  // Print boolean cmp > 0 <0 or ==0
  auto comparison = cmp == 0 ? "==" : (cmp > 0 ? ">" : "<");
  std::cout << str << " " << comparison << " 0" << std::endl;
}
void spaceshipOperator() {
  std::cout << "Spaceship operator:" << std::endl;
  auto cmp = 3 <=> 3;
  printSpaceshipResult("3 <=> 3", cmp);
  cmp = 3 <=> 4;
  printSpaceshipResult("3 <=> 4", cmp);
  cmp = 'a' <=> 'q';
  printSpaceshipResult("a <=> q", cmp);
  cmp = 'z' <=> 'a';
  printSpaceshipResult("z <=> a", cmp);
}
} // namespace CH2

void ch2() {
  std::cout << "Chapter 2: Basic Concepts 1" << std::endl;
  CH2::pointerToAPointer();
  CH2::promotions();
  CH2::implicitPromotion();

  // auto
  std::cout << "DOuble of 5: " << CH2::doubleValue(5) << std::endl;
  CH2::printAuto("Hello");
  CH2::printAuto(40.33);
  CH2::printAuto(false);

  CH2::commaOperator();
  CH2::spaceshipOperator();

  // C++20 comparison
  std::cout << "U8 == S64:\t" << std::cmp_equal((uint8_t)8, (int64_t)8)
            << std::endl;
  std::cout << "Si == U16:\t" << std::cmp_equal(0, (uint16_t)0) << std::endl;
  std::cout << "S8 -1 == U8 255:\t" << std::cmp_equal((int8_t)-1, (uint8_t)255)
            << std::endl;
}