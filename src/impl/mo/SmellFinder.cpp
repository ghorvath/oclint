#include "mo/SmellFinder.h"
#include "mo/TraverseAST.h"
#include "mo/Reporter.h"
#include "mo/Rule.h"
#include "mo/RuleViolation.h"
#include "mo/RuleData.h"
#include "mo/exception/MOException.h"

#include "mo/rule/SwitchStatementRule.h"

SmellFinder::SmellFinder() {
  _data = new RuleData();
  
  // temporarily use a fixed Rule
  _data->addRule(new SwitchStatementRule());
}

SmellFinder::~SmellFinder() {
  delete _data;
  _data = NULL;
}

bool SmellFinder::hasSmell(const CXTranslationUnit& translationUnit) const {
  if (!translationUnit) {
    throw MOException("Inspect on an mpty translation unit!");
  }
  if (clang_getNumDiagnostics(translationUnit)) {
    throw MOException("Insepct on a questionable translation unit!");
  }
  clang_visitChildren(clang_getTranslationUnitCursor(translationUnit), traverseAST, _data);
  return _data->numberOfViolations();
}

const string SmellFinder::reportSmells(const Reporter& reporter) const {
  if (!_data->numberOfViolations()) {
    throw MOException("No violation to report!");
  }
  return reporter.reportViolations(_data->getViolations());
}
