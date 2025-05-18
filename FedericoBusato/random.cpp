// Heaps
#include <functional>
#include <queue>
#include <vector>

using namespace std;
namespace Heaps_Learn {
struct LL {
  int val;
  LL *next;
  LL(int x) : val(x), next(nullptr) {}
};

LL *sortedMerge(vector<LL *> &lists) {
  auto cmp = [](LL *a, LL *b) { return a->val > b->val; };
  priority_queue<LL *, vector<LL *>, decltype(cmp)> minHeap(cmp);
  for (LL *l : lists)
    if (l)
      minHeap.push(l);
  LL dummy(0), *tail = &dummy;
  while (!minHeap.empty()) {
    auto node = minHeap.top();
    minHeap.pop();
    tail = tail->next = node;
    if (auto next = node->next)
      minHeap.push(next);
  }
  return dummy.next;
}

} // namespace Heaps_Learn