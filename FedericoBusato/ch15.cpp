#include <iostream>

using namespace std;

namespace {
void cmake() {
  //
}

void doxygen() {
  /// Comments are Doxygen compatible
  // Prefer clang-doc
}
void stats() {
  //
}
void otherTools() {
  // Code search: ripgrep / Hypergrep : 100x faster than grep
  // FIRACODE: Font with ligatures
}

} // namespace

void ch15() {
  cout << "ch15" << endl;
  cmake();
  doxygen();
  stats();
  otherTools();
}