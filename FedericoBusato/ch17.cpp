#include <algorithm>
#include <cassert>
#include <cstddef>
#include <iostream>
#include <iterator>
using namespace std;

namespace {
void containersAndIterators() {
  // C++STL strongly based on Containers and Iterators
  //
}
void sequenceContainer() {
  //
}
void associativeContainer() {
  //
}
void containerAdapter() {
  //
}
void views() {
  //
}

using value_t = int;
struct List {
  struct Node {
    value_t _value;
    Node *_next;
  };
  Node *_head{nullptr};
  Node *_tail{nullptr};

  /// Insert value at the end
  void push_back(value_t value) {
    Node *new_node = new Node{value, nullptr};
    if (_head == nullptr) {
      _head = new_node;
    } else {
      assert(_tail != nullptr);
      _tail->_next = new_node;
    }
    _tail = new_node;
  }
  /// Iterator
  struct It {
    Node *_ptr;
    It(Node *ptr); // Constructor

    // Dereferencing
    value_t &operator*() { return _ptr->_value; }

    // Not equal
    friend bool operator!=(const It &lhs, const It &rhs) {
      return lhs._ptr != rhs._ptr;
    }

    // Pre Increment
    It operator++() {
      _ptr = _ptr->_next;
      return *this;
    }
    // Post increment
    It operator++(int) {
      auto copy = *this;
      ++(*this);
      return copy;
    }
    // Type traits
    using iterator_category = std::forward_iterator_tag;
    using difference_type = std::ptrdiff_t;
    using value_type = value_t;
    using pointer = value_t *;
    using reference = value_t &;
  };
  It begin() { return It(_head); }
  It end() { return It(_head); }
};

void customIterator() {
  // Custom Iterators
  List list;
  list.push_back(1);
  list.push_back(14);
  list.push_back(33);

  cout << *find(list.begin(), list.end(), 14) << endl;

  for (const auto &it : list)
    cout << it << " ";
}
void iteratorUtility() {
  //
  // std::min_element()
}
void algorithmsLibrary() {
  //
}
void cpp20Ranges() {
  //
}
} // namespace
void ch17() {
  cout << "Chapter 17" << endl;
  containersAndIterators();
  sequenceContainer();
  associativeContainer();
  containerAdapter();
  views();
  customIterator();
  iteratorUtility();
  algorithmsLibrary();
  cpp20Ranges();
}