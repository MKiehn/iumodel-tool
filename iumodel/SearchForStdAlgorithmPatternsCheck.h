//===--- SearchForStdAlgorithmPatternsCheck.h - clang-tidy-------*- C++ -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_CLANG_TOOLS_EXTRA_CLANG_TIDY_IUMODEL_SEARCH_FOR_STD_ALGORITHM_PATTERNS_H
#define LLVM_CLANG_TOOLS_EXTRA_CLANG_TIDY_IUMODEL_SEARCH_FOR_STD_ALGORITHM_PATTERNS_H

#include "../ClangTidy.h"
#include "clang/AST/ASTContext.h"
#include "clang/AST/Decl.h"
#include "clang/AST/RecursiveASTVisitor.h"
#include "clang/AST/Type.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"
#include "llvm/Support/Casting.h"
#include "llvm/Support/raw_os_ostream.h"

#include <algorithm>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>

namespace clang {
namespace tidy {
namespace iumodel {

/// FIXME: Write a short description.
///
/// For the user-facing documentation see:
/// http://clang.llvm.org/extra/clang-tidy/checks/search-for-Std-Algorithm-Patterns.html
class SearchForStdAlgorithmPatternsCheck : public ClangTidyCheck {
 public:
  SearchForStdAlgorithmPatternsCheck(StringRef Name, ClangTidyContext *Context)
      : ClangTidyCheck(Name, Context) {}
  void registerMatchers(ast_matchers::MatchFinder *Finder) override;
  void check(const ast_matchers::MatchFinder::MatchResult &Result) override;

  enum ParseInfo { LogicalSyntax, ControlFlowSyntax };
  struct LSTnode {
    clang::Stmt *stmt;
    clang::VarDecl *decl;
    clang::BinaryOperator *op;

    LSTnode(clang::Stmt *stmt, clang::VarDecl *decl,
            clang::BinaryOperator *op) {
      this->stmt = stmt;
      this->decl = decl;
      this->op = op;
    }

    bool isIterable() const {
      if (this->decl) {
        if (this->decl->getType()->isArrayType()) {
          return true;
        }
      }
      return false;
    }

    bool isVariable() const {
      if (this->decl) {
        if (this->decl->getType()->isArithmeticType()) {
          return true;
        }
      }
      return false;
    }

    bool isOperator() const {
      if (this->op) {
        return true;
      }
      return false;
    }

    bool isBranch() const {
      if (this->stmt) {
        if (isa<IfStmt>(this->stmt) || isa<SwitchStmt>(this->stmt)) {
          return true;
        }
      }
      return false;
    }

    bool isTerminate() const {
      if (this->stmt) {
        if (isa<BreakStmt>(this->stmt) || isa<ReturnStmt>(this->stmt)) {
          return true;
        }
      }
      return false;
    }

    bool equalsVariable(LSTnode otherLSTnode) const {
      if (this->isVariable()) {
        if (otherLSTnode.decl) {
          if (this->decl == otherLSTnode.decl) {
            return true;
          }
        }
      }
      return false;
    }

    bool equalsIterable(LSTnode otherLSTnode) const {
      if (this->isIterable()) {
        if (otherLSTnode.decl) {
          if (this->decl == otherLSTnode.decl) {
            return true;
          }
        }
      }
      return false;
    }
  };

  std::vector<LSTnode> lhsLogicalSyntaxTree;
  std::vector<LSTnode> rhsLogicalSyntaxTree;
  std::vector<LSTnode> controlFlowTree;

  bool hasIterable(std::vector<LSTnode> &LST);
  bool hasVariable(std::vector<LSTnode> &LST);
  bool hasOperator(std::vector<LSTnode> &LST);
  bool hasBranch(std::vector<LSTnode> &ControlFlow);
  bool hasTerminate(std::vector<LSTnode> &ControlFlow);
  bool hasEarlyExit(std::vector<LSTnode> &ControlFlow);

  bool isControlFlowTreeNode(clang::Stmt *node, LSTnode &item);
  bool isLogicalSyntaxTreeNode(clang::Stmt *node, LSTnode &item);
  void traverseSubtree(clang::Expr *node, ParseInfo modus,
                     std::vector<LSTnode> &LST);
  void traverseSubtree(clang::Stmt *node, ParseInfo modus,
                     std::vector<LSTnode> &LST);

  clang::Stmt *getFirstNodeFromExpression(clang::Expr *expr);
  const clang::Stmt *getParentFromASTNode(clang::Stmt *startnode,
                                          const clang::Stmt *endnode,
                                          clang::ASTContext *context);
  void createControlFlowGraph(clang::Stmt *startnode,
                               const clang::Stmt *endnode,
                               clang::ASTContext *context);

  bool isAccumulate(const clang::BinaryOperator *operation,
                    std::vector<LSTnode> &leftLST,
                    std::vector<LSTnode> &rightLST, clang::ASTContext *context);
  bool isTransform(const clang::BinaryOperator *operation,
                   std::vector<LSTnode> &leftLST,
                   std::vector<LSTnode> &rightLST, clang::ASTContext *context);
  bool isFind(const clang::BinaryOperator *operation,
              std::vector<LSTnode> &leftLST, std::vector<LSTnode> &rightLST,
              clang::ASTContext *context);
  bool isCountIf(const clang::Stmt *operation, std::vector<LSTnode> &leftLST,
                 std::vector<LSTnode> &rightLST, clang::ASTContext *context);
  bool isMismatch(const clang::Stmt *secondLoop,
                  const clang::BinaryOperator *operation,
                  std::vector<LSTnode> &leftLST, std::vector<LSTnode> &rightLST,
                  clang::ASTContext *context);
  bool isSearch(const clang::Stmt *secondLoop,
                const clang::BinaryOperator *operation,
                std::vector<LSTnode> &leftLST, std::vector<LSTnode> &rightLST,
                clang::ASTContext *context);

  void loopFind(const clang::BinaryOperator *assignmentOp,
                const clang::BinaryOperator *compareOp,
                const clang::Stmt *countOp, const clang::Stmt *firstLoop,
                const clang::Stmt *secondLoop, clang::ASTContext *context);

  std::string createMessageToUser(StringRef operation, int &lineNumber, std::string algorithm);
};

}  // namespace iumodel
}  // namespace tidy
}  // namespace clang

#endif  // LLVM_CLANG_TOOLS_EXTRA_CLANG_TIDY_IUMODEL_SEARCH_FOR_STD_ALGORITHM_PATTERNS_H
