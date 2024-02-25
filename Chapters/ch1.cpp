#include "common.h"
#include <iostream>
#include <stdio.h>
// Cpp file for ch1.cpp
void ch1() {
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

  // Promotions
  int a = 10;
}