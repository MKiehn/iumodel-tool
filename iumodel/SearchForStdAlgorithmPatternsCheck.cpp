//===--- SearchForStdAlgorithmPatternsCheck.cpp - clang-tidy---------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#include "SearchForStdAlgorithmPatternsCheck.h"
#include "clang/AST/ASTContext.h"
#include "clang/AST/RecursiveASTVisitor.h"
#include "clang/AST/Type.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"
#include "llvm/Support/Casting.h"
#include "llvm/Support/raw_os_ostream.h"

#include <iostream>
#include <string>

using namespace clang::ast_matchers;

namespace clang {
namespace tidy {
namespace iumodel {

static const char foreachMsg[] = "Structure does look like a std::for_each";
static const char transformMsg[] = "Structure does look like a std::transform";
static const char accumulateMsg[] =
    "Structure does look like a std::accumulate";
static const char findMsg[] = "Structure does look like a std::find";
static const char mismatchMsg[] = "Structure does look like a std::mismatch";
static const char searchMsg[] = "Structure does look like a std::search";
static const char countIfMsg[] = "Structure does look like a std::count_if";

void SearchForStdAlgorithmPatternsCheck::registerMatchers(MatchFinder *Finder) {
  StatementMatcher arrayOp = castExpr(hasCastKind(CK_ArrayToPointerDecay));
  StatementMatcher bCountOp =
      binaryOperator(anyOf(hasOperatorName("+"), hasOperatorName("-")));
  StatementMatcher uCountOp =
      unaryOperator(anyOf(hasOperatorName("++"), hasOperatorName("--")))
          .bind("countOp");
  StatementMatcher countOp = anyOf(bCountOp, uCountOp);
  StatementMatcher assignmentOp =
      binaryOperator(anyOf(hasOperatorName("="), hasOperatorName("+="),
                           hasOperatorName("-="), hasOperatorName("*="),
                           hasOperatorName("/="), hasOperatorName("%="),
                           hasOperatorName(">>="), hasOperatorName("<<="),
                           hasOperatorName("&="), hasOperatorName("^="),
                           hasOperatorName("|=")))
          .bind("assignmentOp");
  StatementMatcher compareOp =
      binaryOperator(anyOf(hasOperatorName("=="), hasOperatorName("!=")))
          .bind("compareOp");
  StatementMatcher findRange =
      allOf(hasDescendant(countOp), hasDescendant(arrayOp));
  StatementMatcher findRangeWithAssignment =
      allOf(hasDescendant(countOp), hasDescendant(arrayOp),
            anyOf(hasDescendant(assignmentOp), hasDescendant(compareOp)));
  StatementMatcher findRangeWithRangeAndAssigment =
      allOf(hasDescendant(countOp), hasDescendant(arrayOp),
            anyOf(forStmt(findRangeWithAssignment).bind("secondLoop"),
                  doStmt(findRangeWithAssignment).bind("secondLoop"),
                  whileStmt(findRangeWithAssignment).bind("secondLoop"),
                  cxxForRangeStmt(findRangeWithAssignment).bind("secondLoop")));

  Finder->addMatcher(forStmt(anyOf(findRangeWithRangeAndAssigment,
                                   findRangeWithAssignment, findRange))
                         .bind("ForWithFunctionCallWithArray"),
                     this);
  Finder->addMatcher(doStmt(anyOf(findRangeWithRangeAndAssigment,
                                  findRangeWithAssignment, findRange))
                         .bind("DoWithFunctionCallWithArray"),
                     this);
  Finder->addMatcher(whileStmt(anyOf(findRangeWithRangeAndAssigment,
                                     findRangeWithAssignment, findRange))
                         .bind("WhileWithFunctionCallWithArray"),
                     this);
  Finder->addMatcher(cxxForRangeStmt(anyOf(findRangeWithRangeAndAssigment,
                                           findRangeWithAssignment, findRange))
                         .bind("ForRangeWithFunctionCallWithArray"),
                     this);
}

bool SearchForStdAlgorithmPatternsCheck::isLogicalSyntaxTreeNode(
    clang::Stmt *node, LSTnode &item) {
  if (DeclRefExpr *DeclRef = llvm::dyn_cast<DeclRefExpr>(node)) {
    if (VarDecl *Var = llvm::dyn_cast<VarDecl>(DeclRef->getDecl())) {
      if (Var->getType()->isArrayType() || Var->getType()->isArithmeticType()) {
        item.stmt = node;
        item.decl = Var;
        item.op = nullptr;
        return true;
      }
    }
  }
  if (BinaryOperator *Op = llvm::dyn_cast<BinaryOperator>(node)) {
    item.stmt = node;
    item.decl = nullptr;
    item.op = Op;
    return true;
  }
  return false;
}

bool SearchForStdAlgorithmPatternsCheck::isControlFlowTreeNode(
    clang::Stmt *node, LSTnode &item) {
  if (BreakStmt *terminateStmt = llvm::dyn_cast<BreakStmt>(node)) {
    item.stmt = node;
    item.decl = nullptr;
    item.op = nullptr;
    return true;
  }
  if (ReturnStmt *terminateStmt = llvm::dyn_cast<ReturnStmt>(node)) {
    item.stmt = node;
    item.decl = nullptr;
    item.op = nullptr;
    return true;
  }
  return false;
}

void SearchForStdAlgorithmPatternsCheck::traversingAST(
    clang::Expr *node, ParseInfo modus, std::vector<LSTnode> &LST) {
  if (node->child_end() == node->child_begin()) {
    if (clang::Stmt *singleNode = llvm::dyn_cast<Stmt>(node)) {
      LSTnode item = LSTnode(nullptr, nullptr, nullptr);
      if (modus == ParseInfo::LogicalSyntax) {
        if (isLogicalSyntaxTreeNode(singleNode, item)) {
          LST.push_back(item);
        }
      }
      if (modus == ParseInfo::ControlFlowSyntax) {
        if (isControlFlowTreeNode(singleNode, item)) {
          LST.push_back(item);
        }
      }
    }
    return;
  } else {
    for (auto child : node->children()) {
      if (child) {
        LSTnode item = LSTnode(nullptr, nullptr, nullptr);
        if (modus == ParseInfo::LogicalSyntax) {
          if (isLogicalSyntaxTreeNode(child, item)) {
            LST.push_back(item);
          }
        }
        if (modus == ParseInfo::ControlFlowSyntax) {
          if (isControlFlowTreeNode(child, item)) {
            LST.push_back(item);
          }
        }
        traversingAST(child, modus, LST);
      }
    }
  }
}

void SearchForStdAlgorithmPatternsCheck::traversingAST(
    clang::Stmt *node, ParseInfo modus, std::vector<LSTnode> &LST) {
  for (auto child : node->children()) {
    if (child) {
      LSTnode item = LSTnode(nullptr, nullptr, nullptr);
      if (modus == ParseInfo::LogicalSyntax) {
        if (isLogicalSyntaxTreeNode(child, item)) {
          LST.push_back(item);
        }
      }
      if (modus == ParseInfo::ControlFlowSyntax) {
        if (isControlFlowTreeNode(child, item)) {
          LST.push_back(item);
        }
      }
      traversingAST(child, modus, LST);
    }
  }
}

clang::Stmt *SearchForStdAlgorithmPatternsCheck::getFirstNodeFromExpression(
    clang::Expr *expr) {
  for (auto item : expr->children()) {
    return item;
  }
  return nullptr;
}

const clang::Stmt *SearchForStdAlgorithmPatternsCheck::getParentFromASTNode(
    clang::Stmt *startnode, const clang::Stmt *endnode,
    clang::ASTContext *context) {
  auto parent = context->getParents(*startnode);
  if (auto item = parent[0].get<Stmt>()) {
    return item;
  }
  return nullptr;
}

void SearchForStdAlgorithmPatternsCheck::createdControlFlowGraph(
    clang::Stmt *startnode, const clang::Stmt *endnode,
    clang::ASTContext *context) {
  controlFlowTree.clear();
  const clang::Stmt *item = startnode;
  do {
    item = getParentFromASTNode(startnode, endnode, context);
    if (!item) {
      break;
    }
    if (isa<IfStmt>(item) || isa<SwitchStmt>(item) || isa<CaseStmt>(item)) {
      clang::Stmt *node = const_cast<Stmt *>(item);
      LSTnode branchStmt = LSTnode(node, nullptr, nullptr);
      controlFlowTree.push_back(branchStmt);
      traversingAST(node, ParseInfo::ControlFlowSyntax, controlFlowTree);
    }
    startnode = const_cast<Stmt *>(item);
  } while (item != endnode);
}

bool SearchForStdAlgorithmPatternsCheck::hasIterable(
    std::vector<LSTnode> &LST) {
  for (const auto item : LST) {
    if (item.isIterable()) {
      return true;
    }
  }
  return false;
}

bool SearchForStdAlgorithmPatternsCheck::hasVariable(
    std::vector<LSTnode> &LST) {
  for (const auto item : LST) {
    if (item.isVariable()) {
      return true;
    }
  }
  return false;
}

bool SearchForStdAlgorithmPatternsCheck::hasOperator(
    std::vector<LSTnode> &LST) {
  for (const auto item : LST) {
    if (item.isOperator()) {
      return true;
    }
  }
  return false;
}

bool SearchForStdAlgorithmPatternsCheck::hasBranch(
    std::vector<LSTnode> &ControlFlow) {
  for (const auto item : ControlFlow) {
    if (item.isBranch()) {
      return true;
    }
  }
  return false;
}

bool SearchForStdAlgorithmPatternsCheck::hasTerminate(
    std::vector<LSTnode> &ControlFlow) {
  for (const auto item : ControlFlow) {
    if (item.isTerminate()) {
      return true;
    }
  }
  return false;
}

bool SearchForStdAlgorithmPatternsCheck::hasEarlyExit(
    std::vector<LSTnode> &ControlFlow) {
  if (hasBranch(ControlFlow) && hasTerminate(ControlFlow)) {
    return true;
  }
  return false;
}

bool SearchForStdAlgorithmPatternsCheck::isAccumulate(
    const BinaryOperator *operation, std::vector<LSTnode> &leftLST,
    std::vector<LSTnode> &rightLST, clang::ASTContext *context) {
  if (operation->isCompoundAssignmentOp() &&
      !operation->getOpcodeStr().equals(StringRef("-="))) {
    if (hasVariable(leftLST) && hasIterable(rightLST)) {
      return true;
    }
  }
  if (operation->isAssignmentOp()) {
    if (hasVariable(leftLST) && !hasIterable(leftLST) &&
        !hasOperator(leftLST) && hasVariable(rightLST) &&
        hasIterable(rightLST) && hasOperator(rightLST)) {
      for (auto itemLeft : leftLST) {
        if (itemLeft.isVariable()) {
          for (auto itemRight : rightLST) {
            if (itemLeft.equalsVariable(itemRight)) {
              return true;
            }
          }
        }
      }
    }
  }
  return false;
}

bool SearchForStdAlgorithmPatternsCheck::isTransform(
    const clang::BinaryOperator *operation, std::vector<LSTnode> &leftLST,
    std::vector<LSTnode> &rightLST, clang::ASTContext *context) {
  if (operation->isCompoundAssignmentOp() || operation->isAssignmentOp()) {
    if (hasIterable(leftLST) && hasIterable(rightLST)) {
      return true;
    }
  }
  return false;
}

bool SearchForStdAlgorithmPatternsCheck::isFind(
    const clang::BinaryOperator *operation, std::vector<LSTnode> &leftLST,
    std::vector<LSTnode> &rightLST, clang::ASTContext *context) {
  if (operation->isComparisonOp()) {
    if ((hasIterable(leftLST) && hasVariable(rightLST) &&
         !hasIterable(rightLST)) ||
        (hasVariable(leftLST) && !hasIterable(leftLST) &&
         hasIterable(rightLST))) {
      if (hasEarlyExit(controlFlowTree)) {
        return true;
      }
    }
  }
  return false;
}

bool SearchForStdAlgorithmPatternsCheck::isMismatch(
    const clang::Stmt *secondLoop, const clang::BinaryOperator *operation,
    std::vector<LSTnode> &leftLST, std::vector<LSTnode> &rightLST,
    clang::ASTContext *context) {
  if (secondLoop) {
    if (operation->getOpcodeStr().equals(StringRef("!="))) {
      if (hasIterable(leftLST) && hasIterable(rightLST)) {
        for (auto itemLeft : leftLST) {
          if (itemLeft.isIterable()) {
            for (auto itemRight : rightLST) {
              if (itemRight.isIterable()) {
                if (itemRight.equalsIterable(itemLeft)) {
                  return false;
                }
              }
            }
          }
        }
        if (hasEarlyExit(controlFlowTree)) {
          return true;
        }
        return false;
      }
    }
  }
  return false;
}

bool SearchForStdAlgorithmPatternsCheck::isSearch(
    const clang::Stmt *secondLoop, const clang::BinaryOperator *operation,
    std::vector<LSTnode> &leftLST, std::vector<LSTnode> &rightLST,
    clang::ASTContext *context) {
  if (secondLoop) {
    if (operation->getOpcodeStr().equals(StringRef("=="))) {
      if (hasIterable(leftLST) && hasIterable(rightLST)) {
        if (hasEarlyExit(controlFlowTree)) {
          return true;
        }
      }
    }
  }
  return false;
}

bool SearchForStdAlgorithmPatternsCheck::isCountIf(
    const clang::Stmt *operation, std::vector<LSTnode> &leftLST,
    std::vector<LSTnode> &rightLST, clang::ASTContext *context) {
  if (const clang::UnaryOperator *op =
          llvm::dyn_cast<clang::UnaryOperator>(operation)) {
    if (hasBranch(controlFlowTree)) {
      return true;
    }
  }
  return false;
}

void SearchForStdAlgorithmPatternsCheck::loopFind(
    const clang::BinaryOperator *assignmentOp,
    const clang::BinaryOperator *compareOp, const clang::Stmt *countOp,
    const clang::Stmt *firstLoop, const clang::Stmt *secondLoop,
    clang::ASTContext *context) {
  lhsLogicalSyntaxTree.clear();
  rhsLogicalSyntaxTree.clear();

  if (assignmentOp || compareOp) {
    clang::Expr *opLHS;
    clang::Expr *opRHS;

    if (assignmentOp) {
      opLHS = assignmentOp->getLHS();
      opRHS = assignmentOp->getRHS();
      clang::Stmt *firstNode = getFirstNodeFromExpression(opLHS);
      if (firstNode && firstLoop) {
        createdControlFlowGraph(firstNode, firstLoop, context);
      }
    }

    if (compareOp) {
      opLHS = compareOp->getLHS();
      opRHS = compareOp->getRHS();
      clang::Stmt *firstNode = getFirstNodeFromExpression(opLHS);
      if (firstNode && firstLoop) {
        createdControlFlowGraph(firstNode, firstLoop, context);
      }
    }

    traversingAST(opLHS, ParseInfo::LogicalSyntax, lhsLogicalSyntaxTree);
    traversingAST(opRHS, ParseInfo::LogicalSyntax, rhsLogicalSyntaxTree);

    if (lhsLogicalSyntaxTree.empty() || rhsLogicalSyntaxTree.empty()) {
      return;
    }

    if (assignmentOp) {
      if (isAccumulate(assignmentOp, lhsLogicalSyntaxTree, rhsLogicalSyntaxTree,
                       context)) {
        diag(firstLoop->getLocStart(), accumulateMsg);
      }
      if (isTransform(assignmentOp, lhsLogicalSyntaxTree, rhsLogicalSyntaxTree,
                      context)) {
        diag(firstLoop->getLocStart(), transformMsg);
      }
    }
    if (compareOp) {
      if (isFind(compareOp, lhsLogicalSyntaxTree, rhsLogicalSyntaxTree,
                 context)) {
        diag(firstLoop->getLocStart(), findMsg);
      }
      if (isMismatch(secondLoop, compareOp, lhsLogicalSyntaxTree,
                     rhsLogicalSyntaxTree, context)) {
        diag(firstLoop->getLocStart(), mismatchMsg);
      }
      if (isSearch(secondLoop, compareOp, lhsLogicalSyntaxTree,
                   rhsLogicalSyntaxTree, context)) {
        diag(firstLoop->getLocStart(), searchMsg);
      }
    }
  }
  if (countOp) {
    if (firstLoop) {
      clang::Stmt *node = const_cast<Stmt *>(countOp);
      createdControlFlowGraph(node, firstLoop, context);
    }
    if (isCountIf(countOp, lhsLogicalSyntaxTree, rhsLogicalSyntaxTree,
                  context)) {
      diag(firstLoop->getLocStart(), countIfMsg);
    }
  }
}

void SearchForStdAlgorithmPatternsCheck::check(
    const MatchFinder::MatchResult &Result) {
  const auto *assignmentOp =
      Result.Nodes.getNodeAs<clang::BinaryOperator>("assignmentOp");
  const auto *compareOp =
      Result.Nodes.getNodeAs<clang::BinaryOperator>("compareOp");
  const auto *countOp = Result.Nodes.getNodeAs<clang::Stmt>("countOp");
  const auto *secondLoop = Result.Nodes.getNodeAs<clang::Stmt>("secondLoop");
  auto *context = Result.Context;

  if (const auto *match = Result.Nodes.getNodeAs<clang::ForStmt>(
          "ForWithFunctionCallWithArray")) {
    loopFind(assignmentOp, compareOp, countOp, match, secondLoop, context);
  }
  if (const auto *match = Result.Nodes.getNodeAs<clang::DoStmt>(
          "DoWithFunctionCallWithArray")) {
    loopFind(assignmentOp, compareOp, countOp, match, secondLoop, context);
  }
  if (const auto *match = Result.Nodes.getNodeAs<clang::WhileStmt>(
          "WhileWithFunctionCallWithArray")) {
    loopFind(assignmentOp, compareOp, countOp, match, secondLoop, context);
  }
  if (const auto *match = Result.Nodes.getNodeAs<clang::CXXForRangeStmt>(
          "ForRangeWithFunctionCallWithArray")) {
    loopFind(assignmentOp, compareOp, countOp, match, secondLoop, context);
  }
}

}  // namespace iumodel
}  // namespace tidy
}  // namespace clang
