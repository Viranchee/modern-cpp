#include <iostream>

using namespace std;

namespace CH11 {

void translationUnitsConcepts();
void storageClassDuration();
void linkageConstExprVariables();
void linkageSummary();
void multipleTranslationUnits();
void oneDefRule();
void oneDefFunctionTemplate();
void oneDefClassTemplate();
void oneDefBehaviorSummary();
} // namespace CH11
void ch11() {
  cout << "Chapter 11: Trnslation Units 1" << endl;
  CH11::translationUnitsConcepts();
  CH11::storageClassDuration();
  CH11::linkageConstExprVariables();
  CH11::linkageSummary();
  CH11::multipleTranslationUnits();
  CH11::oneDefRule();
  CH11::oneDefFunctionTemplate();
  CH11::oneDefClassTemplate();
  CH11::oneDefBehaviorSummary();
}

void CH11::translationUnitsConcepts() {
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
void CH11::storageClassDuration() {
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
void CH11::linkageConstExprVariables() {
  //
}

void CH11::linkageSummary() {
  //
}
void CH11::multipleTranslationUnits() {
  //
}
void CH11::oneDefRule() {
  //
}
void CH11::oneDefFunctionTemplate() {
  //
}
void CH11::oneDefClassTemplate() {
  //
}
void CH11::oneDefBehaviorSummary() {
  //
}