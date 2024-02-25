#include "common.h"
#include <cstdint>
#include <cstdio>
#include <iostream>
#include <stdio.h>

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

auto doubleValue(int x) { return x * 2; } // C++ 17
void doubleValue(auto x) { printf(x); }   // C++ 20

void ch1() {
  pointerToAPointer();
  promotions();
  // Implicit promotion
  char a = '0';
  std::cout << "a: " << a << std::endl;
  std::cout << "+a: " << +a << std::endl;
  std::cout << "a+0: " << (a + 0) << std::endl;
  std::cout << "a+a: " << (a + a) << std::endl;
}