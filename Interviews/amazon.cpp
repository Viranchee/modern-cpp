#include <vector>

using namespace std;

vector<int> minimalHeaviestSetA(vector<int> arr) {
  // Write your code here
  vector<int> result;
  int sum = 0;
  int max = 0;
  int maxIndex = 0;
  for (int i = 0; i < arr.size(); i++) {
    sum += arr[i];
    if (arr[i] > max) {
      max = arr[i];
      maxIndex = i;
    }
  }
  int half = sum / 2;
  int currentSum = 0;
  for (int i = 0; i < arr.size(); i++) {
    if (i != maxIndex) {
      currentSum += arr[i];
      result.push_back(i);
    }
    if (currentSum > half) {
      break;
    }
  }
  return result;
}