#ifndef MO_UTIL_CCNCOUNTERUTIL_H
#define MO_UTIL_CCNCOUNTERUTIL_H

#include <clang-c/Index.h>

namespace clang {
  class Stmt;
  class Expr;
}

class CCNCounterUtil {
public:
  static int getCCNOfCursor(CXCursor node);
};

bool isDecisionPoint(clang::Stmt *stmt);
bool isDecisionPoint(clang::Expr *expr);
enum CXChildVisitResult ccnTraverseAST(CXCursor node, CXCursor parentNode, CXClientData clientData);

#endif
