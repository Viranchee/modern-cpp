#include <iostream>
#include <regex>
#include <set>
#include <vector>
using namespace std;

void foo() {
  int arr[100]; // initialized to some data, indices : 0 to 99

  // A & B Updated here?
  int ab = 1 * 1; // a * b; // Runtime constant
  for (unsigned int i = 0; i < 100; i++) {
    int incData = ab + i; // Read from file
    arr[i + 1] += incData;
  } // ISSUE: arr[0] not updated, arr[100] out of bounds accessed

  unsigned int i = 100;

  while (i >= 0) {
    i--;                    // 99 to -1
    cout << arr[i] << endl; // Uses arr[99] ✅ , arr[-1] OUT OF BOUNDS
  }
}

/*

// Q1: Given an array of integers nums containing n integers find the first
repeating number in "nums"

input: nums = [1,3,4,2,2] // Use a set
output: 2
input: nums = [1,3,3,2,2]
output: 3
input: nums = [1,3,2,3,2]
output: 3
*/
int firstRepeatingNumber(std::vector<int> input) {
  std::set<int> visited; // FIXME: Unordered_SET
  for (auto value : input) {
    // Find in set if value is present
    if (visited.contains(value)) {
      // If present, that's the first repeating
      return value;
    } else {
      visited.insert(value);
    }
    // Else, insert in the set
  }
}
/*
// Q2: Given an array of integers nums containing 1s and 0s. Return the maximum
consecutive 1s. You can flip one 0 to make maximum consecutive 1's input: nums =
[1,0,1,1,0] output: 4 input: nums = [0,0,1,1,0] output: 3
*/
int maxConsequetiveOnes(vector<int> input) {
  struct Group {
    int number;
    int repeatCount;
  };
  vector<Group> groups;
  for (auto val : input) {
    Group *currentGroup;
    if (!groups.empty()) {
      currentGroup = groups.back();
      if (currentGroup->number == val) {
        currentGroup->repeatCount++;
      }
    } else {
      currentGroup->number = val;
      currentGroup->repeatCount = 1;
    }
  }
}

/*
 4 (Compiler Optimization):
Question:
Say I have some assembly instruction that is an  “or” operation between two
unsigned 64bit values. I know that the upper 32 bits of both inputs are 0’s.
Based on the chart below what instruction(s) can I replace this “or” operation
with to optimize my code to run in the least amount of cycles? Instruction

Cycle Cost
6 cycles

64bit "OR"

32bit "OR"
1 cycle

64bit -> 32bit "Truncate"
1 cycle

32bit -> 64bit "Zero Extend"
1 cycle

32bit ShL/ShR "Logical Shift"
1 cycle
 */

/*
i1 64 (32)
i2 64 (32)

si1 = trunc i1
si2 = trunc i2
si3 = or32 si1 si2
i3  = zext si3
*/