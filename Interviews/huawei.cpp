// Given an array of integers, the task is to remove an element from the array
// to make the array sorted (either ascending or descending). 1.	If the
// array is sorted already, return the smallest element of the array 2.	If the
// array is not sorted, a)	If removing one of its elements makes it sorted,
// return this element; if multiple solutions exist, return the smallest element
// of the solutions b)	If no any solutions, return -1

// Input:
// 1st line: an integer between 2 and 200 (2 and 200 are included) which is the
// length of an array 2nd line: all elements of the array, each element is in
// the range of [0.200]

#include "stdio.h"
#include <cstddef>
#include <map>
#include <vector>
using namespace std;
int huaweiTask(std::vector<int> input);

int main() {
  //  4 5 6 1 2 3
}

enum Order { Inc, Dec };
int huaweiTask(std::vector<int> input) {
  // if Input is sorted, return smallest element
  vector<Order> inputOrder(input.size() - 1);
  int totalCount[2];
  totalCount[0] = 0;
  totalCount[1] = 0;
  for (size_t i = 0; i < input.size() - 2; i++) {
    Order order = input[i] < input[i + 1] ? Inc : Dec;
    totalCount[order]++;
    inputOrder[i] = order;
  }
  { // 1
    if (totalCount[0] == (int)input.size() - 2) {
      // Ascending order
      return input[0];
    }

    if (totalCount[1] == (int)input.size() - 2) {
      return input[input.size() - 1];
    }
  }
  { // 2
    // a.
    if (totalCount[0] == 1) {
    }
    if (totalCount[1] == 1) {
    }
  }
}