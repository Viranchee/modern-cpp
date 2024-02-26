#include <iostream>
#include <stdexcept>

using namespace std;

// Data and BSS segment: Static/Global data
// Larger than stack but slower

int globalData[] = {1, 2}; // Data segment
int globalBss[1'000'000];  // BSS segment

void heapAndStack() {
  /*
   Stack segment: 1MB (Windows) or 8MB (Linux)
   if exceeded, hard crash
   1 stack per thread
  */
  [[maybe_unused]] int stackData[] = {1, 2};
  /*
   Heap segment: If exceed, Exception or nullptr
   shared among threads, 1 heap per process
  */
  [[maybe_unused]] int *heapData = new int[1'000'000];
  delete[] heapData;

  [[maybe_unused]] int eitherStackOrRegister = 0; // Either stack or register
  [[maybe_unused]] struct {
    int a;
  } someStruct; // Either stack or register, where the struct is allocated
  [[maybe_unused]] void *ptr = malloc(40); // ptr is on stack, 40 bytes on heap
  free(ptr);

  const char *str = "abc";
  if (true) {
    char xyz[] = "xyz";
    str = xyz; // OK
  }
  cout << str << endl;

  /*
  new / delete returns exact data type,
  malloc / free returns void* and need to cast

  new throws exception: Cannot be ignored
  malloc returns NULL nullptr: Zero size allocations do not need special code

  Alloc size:
  new:        automatically calculated
  malloc:     manually calculated by the programmer

  Initialization:
  new:        automatically initialized
  malloc:     not initialized. use calloc or memset

  Polymorphism:
  new:        automatically calls constructor. Objects with virtual functions
  must be allocated with new to initialize the vtable pointer
  */
  {
    int *value = (int *)malloc(sizeof(int));
    *value = 10;
    free(value);
    value = new int(10); // new with initialization
    delete value;

    int *array = (int *)malloc(10 * sizeof(int));
    for (int i = 0; i < 10; i++)
      array[i] = i;
    free(array);
    array = new int[10](); // new with initialization
    delete[] array;
  }
  {

    struct MyStruct {
      int a;
      int b;
    } tempStruct;
    tempStruct.a = 10;
    tempStruct.b = -20;
    MyStruct *array = (MyStruct *)malloc(10 * sizeof(MyStruct));
    for (int i = 0; i < 10; i++) {
      array[i] = tempStruct;
      if (array[i].a != tempStruct.a || array[i].b != tempStruct.b)
        cout << "ERROR: Did not copy correctly" << endl;
    }
    free(array);
    array = new MyStruct[10](); // new with initialization
    for (int i = 0; i < 10; i++) {
      array[i] = tempStruct;
      if (array[i].a != tempStruct.a || array[i].b != tempStruct.b)
        cout << "ERROR: Did not copy correctly" << endl;
    }
    delete[] array;
  }
  {
    cout << "Zero initialize" << endl;
    // Zero initialize
    int *array = (int *)calloc(10, sizeof(int));
    free(array);
    array = new int[10](); // new with initialization
  }
  {
    // Matrix allocation
    const int dim = 10;
    int **matrix;
    matrix = new int *[dim];
    for (int i = 0; i < dim; i++) {
      matrix[i] = new int[dim]();
      for (int j = 0; j < dim; j++) {
        matrix[i][j] = (i + 1) * (j + 1);
        // cout << matrix[i][j] << "\t";
      }
      // cout << endl;
    }

    // Free memory
    for (int i = 0; i < dim; i++)
      delete[] matrix[i];
    delete[] matrix;

    // Need to know 2nd dim at compile time.
    auto newMatrix = new int[dim][dim]();
    delete[] newMatrix;
  }
  {
    struct MyStruct {
      int a;
      int b;
    };
    MyStruct *array = new MyStruct[10]();
    delete[] array;
  }

  struct {
    int *p1;
    int *p2;
  } escapee;

  { // Auto, non-allocating placement
    // Works with ptr types only
    // Stack Placement
    int arrayInStack[10];
    int *ptr = new (arrayInStack) int;
    *ptr = 100; // No need to delete ptr
    cout << "Add: " << &ptr << endl;
    escapee.p1 = ptr;

    // HEAP Placement
    int *arrayInHeap = new int[10];
    int *ptr2 = new (arrayInHeap) int;
    *ptr2 = 256; // No need to delete ptr
    cout << "Add: " << &ptr << endl;
    escapee.p2 = ptr2;
    delete[] arrayInHeap;
  }
  cout << "Did pointer escape make through?" << endl;
  cout << &escapee.p1 << ":" << *escapee.p1 << "\t" << &escapee.p2 << ":"
       << *escapee.p2 << endl;

  //  Stack escape stayed, and a new value was allocated.
  // Memory did get free

  // Lets try to free the memory
  //   delete escapee.p1; // Error: double free
  //   delete escapee.p2; // Error: double free
  {

    // Structs can have destructors too

    struct StackStruct {
      int a;
      int b;
      ~StackStruct() { cout << "StackStruct destroyed" << endl; }
    };
    char buffer[10];
    auto storedOnStack = new (buffer) StackStruct();
    // delete storedOnStack; // Runtime Error: Not on heap
    storedOnStack->~StackStruct();
  }

  //
  {
    // NO-Throw
    // Allocation fails for 36 TB
    int *ptr = new (nothrow) int[36'000'000'000'000];
    if (ptr == nullptr)
      cout << "36 TB Allocation failed" << endl;
    else
      delete[] ptr;

    struct Throws {
      Throws() { throw runtime_error("Throws constructor"); }
      ~Throws() { cout << "Throws destructor" << endl; }
    };

    // Allocation throws
    // Throws *thrower = new (nothrow) Throws();

    // Memory Leak
    [[maybe_unused]] int *leak = new int;
    auto bkp = leak;
    // Memory now leaks, because it can never be freed
    leak = nullptr;
    delete bkp;
  }
  {                   // Dynamic Memory Allocation
    int *x = new int; // OS gives in 4KB pages
    // M1 allocates approx 256k Integers, i.e. 1MB of Page size
    auto iterations = (1 << 18);
    cout << "Allocating " << iterations << " page size" << endl;
    int i;
    for (i = 0; i < iterations * 97 / 100; i++) {
      x[i] = i;
    }
    cout << i << " integers allocated" << endl;
    // delete x;
  }
}

void initialization() {
  {
    [[maybe_unused]] int a1;
    [[maybe_unused]] int a2(2);
    [[maybe_unused]] int a5 = 5;
    [[maybe_unused]] int a6 = 2u; // with implicit conversion
    [[maybe_unused]] int a7 = int();
    [[maybe_unused]] int a8 = int(42);
    [[maybe_unused]] int a9 = {100};
    [[maybe_unused]] int a10{1023};
  }
}
void pointerAndReference() {}
void constantAndLiterals() {}
void volatility() {}
void explicts() {}
void sizeOf() {}
// ch5.cpp
void ch5() {
  cout << "Chapter 5: Memory" << endl;
  heapAndStack();
  initialization();
  pointerAndReference();
  constantAndLiterals();
  volatility();
  explicts();
  sizeOf();
}