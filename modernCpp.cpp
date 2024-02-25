/*
Something new: spaceship operator <=>

*/

// #include "mlir/"
// #include "llvm/"
#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <stdio.h>

// #include "llvm
void ch1();

int main(int argc, char **argv) {
  ch1();
  return 0;
}

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
}
