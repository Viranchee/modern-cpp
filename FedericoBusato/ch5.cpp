#include <cstddef>
#include <iostream>
#include <stdexcept>
#include <sys/_types/_u_int8_t.h>

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
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-variable"

  {
    int a1;
    int a2(2);
    int a5 = 5;
    int a6 = 2u; // with implicit conversion
    int a7 = int();
    int a8 = int(42);
    int a9 = {100};
    int a10{1023};
  }

  { // Non static Data member init
    struct S {
      unsigned x = 3; // Equal init
      unsigned y{4};  // Brace init
    };
    // push and pop -Wunused-variable

    S s1;               // Default constructor
    S s2{};             // Default constructor
    S s3{100, -(-100)}; // Sets values
    cout << "Default constructor: \t" << s1.x << ", " << s1.y << endl;
    S s4 = {.y = 100}; // Designated Initializer, x = original init
    // Destructuring / Structured binding
    auto [x, y] = s4;
    int b[2] = {1, 2}; // Array
    auto [b1, b2] = b;
    auto [t1, t2] = tuple<float, int>{3.14f, 42};
  }
#pragma GCC diagnostic pop
}
void pointerAndReference() {
  {
    int *pointer;
    pointer = nullptr;
    pointer = new int;
    cout << "\tPtr: " << pointer;
    *pointer = 10;
    cout << hex;
    cout << "\tV: 0x" << *pointer << endl;
    // Get value stored at pointer's pointer
    cout << "\tV: 0x" << **(int **)&pointer << endl;
    cout << dec;
    delete pointer;
  }
  {
    // Pointers can be converted.
    // Static_cast is not allowed, except for void*
    int a = 420;
    int *ptr = &a;
    cout << "Ptr: " << ptr << "\tV: " << *ptr << "\tA: " << &ptr << endl;
    cout << "Ptr: " << ptr << "\tV: " << *ptr << "\tA: " << &ptr << endl;
    // Reference syntax
    int &ref = *ptr;
    cout << "RefV: " << ref << "\tA: " << &ref << "\tRef" << ref << endl;
    //
  }
  {                            // Wild and dangling pointer
    [[maybe_unused]] int *ptr; // Wild pointer
    int *array = new int[10];
    cout << "Memory created at: \t" << array << endl;
    delete[] array;
    // Dangling pointer: Pointer to memory that has been freed
    cout << "Dangling pointer, Memory already freed at: " << array << endl;
    array = nullptr; // No more side effects
    delete[] array;
  }
  {
    // References
    // Safer than pointers, cannot be changed
    int value = 420;
    int &ref = value;
    int &ref2 = ref;
    ref2++;
    ref++;
    cout << "Double ref, init = 420, ref2++: " << ref2 << endl;

    // Pointers
    int *ptr = &value;
    int *ptr2 = &value;
    ptr++;
    (*ptr2)++;
    int &newRef = value;
    newRef++;
    cout << "Triple inc, init = 420, ptr2++, *ptr++, ref++: " << value << endl;
  }
  {
    // References can be used to indicate fixed size arrays in Function
    // Arguments
  }
}
void constantAndLiterals() {
  { // const
    // Literal, "literal", nullptr, user defined literals

    // Pass by reference, can use const
    // void f1(const int *array) {}

    // Pas by value, and const: Not useful
    // void f2(const int x) {}

    // const and int:
    // Pointer Type     Pointer var?    Pointed value var?
    // int*             var             var
    // const int*       const           var
    // int* const       var             const
    // const int* const const           const (west notation)
    // int const*       const           const (east notation)
  }
  { // constexpr
    // const: Fixed overall the execution of program
    // constexpr: Fixed at compile time

    // Pros: Helps performance & memory usage
    // Pros: Impacts compilation time
    /*
    eg.

    constexpr int square(int val) {
      return val * val;
    }
    square(10); // Compile time evaluation
    int a = 10;
    square(a); // Run time evaluation

    CAN NOT CONTAIN try-catch, exceptions, RTTI, goto, asm, static, undefined
    behavior (reinterpret_cast), unsafe union usage, overflow (signed int), etc
    // assert() : C++14
    // virtual: C++20

    Non-Static member functions of run-time objects can never be used in
    constexpr

    Can use `static constexpr`

    */
  }
  { // consteval
    /*
    Guarantees compile time evaluation of a function.
    A non constant value produces compilation error

    consteval int square(int val) {
      return val * val;
    }

    square(10); // Compile time evaluation
    int a = 10;
    square(a); // Compile Error
    */
  }
  { // constinit
    /*

  Compile time initializition
  constexpr int square(int val) {
    return val * val;
  }
  constinit int a = square(10); // Compile time evaluation
  a = 420; Yes can change

    */
  }
  { // if-constexpr
    /*
    auto f() {
      if constexpr (sizeof(int) == 4)
        return 4;
      else
        return 8;
    }

    Ternary NOT SUPPORTED

    Compile time branching, producing less Assembly code

    std::is_constant_evaluated() : C++20 BUGGY

    Solution: if consteval

     */
  }
}
void volatility() {
  {
    /*
    Avoid aggressive memory optimizations involving a pointer or object

    Uses:
    1. Low level programming: Driver, Interaction with Assembly
    Force writing to a specific memory location

    2. Multithreading: Variables shared between threads/processes to
    communicate. Don't optimize, delay update

    3. Benchmarking: Some ops need to not be optimized away

    Note: volatile reads/writes can still be reordered w.r.t. non-volatile
    onessd
    */
  }
  {
    volatile int *ptr = new int[1];
    int pos = 128 * 1024 / sizeof(int);
    ptr[pos] = 10; // SEGFAULT
  }
}
void explicts() {
  {
    const int a = 10;
    [[maybe_unused]] auto ptr = &a;
    [[maybe_unused]] auto b = static_cast<long>(a);
    [[maybe_unused]] auto c = const_cast<int &>(a);
    [[maybe_unused]] auto d = reinterpret_cast<int *>(a);

    // Reinterpret cast: bit level conversion of float to int
    float x = 3.0f;
    [[maybe_unused]] auto e = reinterpret_cast<int &>(x);
    int *ptr2 = new int;
    [[maybe_unused]] int x2 = reinterpret_cast<size_t>(ptr2);

    // Array reshaping
    int matrix[3][4];
    [[maybe_unused]] int(&matrix2)[2][6] =
        reinterpret_cast<int(&)[2][6]>(matrix);
    [[maybe_unused]] int(*arrayRep)[6] = reinterpret_cast<int(*)[6]>(matrix);
  }
  {
    /*
    Type Puning
    Circumventing the type system of a programming language
    To achieve an effect difficult/impossible to achieve within the bounds of
    the formal language.


    float abs(float x) {
      return (x < 0.0f) ? -x : x;
    }

    // TYPE PUNING, UNDEFINED BEHAVIOR
    float optimizedAbs(float x) {
      int *ptr = reinterpret_cast<int *>(&x);
      *ptr &= 0x7FFFFFFF;
      return reinterpret_cast<float &>(ptr);
    }

    Avoiding undefined behavior: use memcpy

    float v1 = 32.3f;
    unsigned v2;
    std::memcpy(&v2, &v1, sizeof(float));

    Option 2: C++ 20: bit_cast

    float v1 = 32.3f;
    unsigned v2 = std::bit_cast<unsigned>(v1);
    */
  }
}
void sizeOf() {
  // Compile time operator. Size in bytes

  // returns size_t (unsigned max width int)
  // 0 only for empty array
  // 1 for empty struct
  // Takes Padding into account
}
// ch5.cpp
void ch5() {
  cout << "Chapter 5: Memory" << endl;
  // heapAndStack();
  // initialization();
  // pointerAndReference();
  // constantAndLiterals();
  volatility();
  explicts();
  sizeOf();
}