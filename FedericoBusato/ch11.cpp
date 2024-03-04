#include "ch11.hpp"
#include <iostream>

using namespace std;

static void translationUnitsConcepts();
static void storageClassDuration();
static void linkageConstExprVariables();
static void linkageSummary();
static void multipleTranslationUnits();
static void oneDefRule();
static void oneDefFunctionTemplate();
static void oneDefClassTemplate();
static void oneDefBehaviorSummary();

void ch11() {
  cout << "Chapter 11: Trnslation Units 1" << endl;
  translationUnitsConcepts();
  storageClassDuration();
  linkageConstExprVariables();
  linkageSummary();
  multipleTranslationUnits();
  oneDefRule();
  oneDefFunctionTemplate();
  oneDefClassTemplate();
  oneDefBehaviorSummary();
}
// https://www.linkedin.com/jobs/view/3835349064

static void translationUnitsConcepts() {
  /*
  Header: Interfaces
  Source: Implementation

  Scopes

  Linkage:
  Internal: Symbols visible only within the translation unit.
  Same symbol has different address in different translation units.
  External: Symbols which exist outside a single translation unit.
  */
  //
}
static void storageClassDuration() {
  /*
  Auto: block start & end
  Static: Program start & end
  Dynamic: Memory alloc & dealloc
  Thread: Thread start & end

  Static Global: Internal to the file
  Non-static Global: Global linkage, name collisions possible

  Extern: Declare existence of global variable/function in another translation
  unit
  External Linkage
  */
}

namespace CH11 {
void lol() { cout << "lol" << endl; }
} // namespace CH11

static void linkageConstExprVariables() {
  CH11::lol();

  //
}
static void linkageSummary() {
  //
}
static void multipleTranslationUnits() {
  //
}
static void oneDefRule() {
  //
}
static void oneDefFunctionTemplate() {
  //
}
static void oneDefClassTemplate() {
  //
}
static void oneDefBehaviorSummary() {
  //
}