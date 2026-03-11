//////////////////////////////////////////////////////////////////////
//
//    TypeCheckVisitor - Walk the parser tree to do the semantic
//                       typecheck for the Asl programming language
//
//    Copyright (C) 2020-2030  Universitat Politecnica de Catalunya
//
//    This library is free software; you can redistribute it and/or
//    modify it under the terms of the GNU General Public License
//    as published by the Free Software Foundation; either version 3
//    of the License, or (at your option) any later version.
//
//    This library is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
//    Affero General Public License for more details.
//
//    You should have received a copy of the GNU Affero General Public
//    License along with this library; if not, write to the Free Software
//    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
//
//    contact: José Miguel Rivero (rivero@cs.upc.edu)
//             Computer Science Department
//             Universitat Politecnica de Catalunya
//             despatx Omega.110 - Campus Nord UPC
//             08034 Barcelona.  SPAIN
//
//////////////////////////////////////////////////////////////////////

#include "TypeCheckVisitor.h"

#include <iostream>
#include <string>

#include "../common/SemErrors.h"
#include "../common/SymTable.h"
#include "../common/TreeDecoration.h"
#include "../common/TypesMgr.h"
#include "antlr4-runtime.h"

// uncomment the following line to enable debugging messages with DEBUG*
// #define DEBUG_BUILD
#include "../common/debug.h"

// using namespace std;

// Constructor
TypeCheckVisitor::TypeCheckVisitor(TypesMgr &Types, SymTable &Symbols,
                                   TreeDecoration &Decorations,
                                   SemErrors &Errors)
    : Types{Types},
      Symbols{Symbols},
      Decorations{Decorations},
      Errors{Errors} {}

// Accessor/Mutator to the attribute currFunctionType
TypesMgr::TypeId TypeCheckVisitor::getCurrentFunctionTy() const {
  return currFunctionType;
}

void TypeCheckVisitor::setCurrentFunctionTy(TypesMgr::TypeId type) {
  currFunctionType = type;
}

// Methods to visit each kind of node:
//
std::any TypeCheckVisitor::visitProgram(AslParser::ProgramContext *ctx) {
  DEBUG_ENTER();
  SymTable::ScopeId sc = getScopeDecor(ctx);
  Symbols.pushThisScope(sc);
  for (auto ctxFunc : ctx->function()) {
    visit(ctxFunc);
  }
  if (Symbols.noMainProperlyDeclared()) Errors.noMainProperlyDeclared(ctx);
  Symbols.popScope();
  Errors.print();
  DEBUG_EXIT();
  return 0;
}

std::any TypeCheckVisitor::visitFunction(AslParser::FunctionContext *ctx) {
  DEBUG_ENTER();
  SymTable::ScopeId sc = getScopeDecor(ctx);
  Symbols.pushThisScope(sc);

  // Get the expected return type directly from the tree decoration
  // instead of risking a local variable shadowing the function name.
  TypesMgr::TypeId funReturn = Types.createVoidTy();
  if (ctx->type()) {
    funReturn = getTypeDecor(ctx->type());
  }

  setCurrentFunctionTy(funReturn);

  if (ctx->funParDeclaration()) {
    visit(ctx->funParDeclaration());
  }

  visit(ctx->declarations());
  visit(ctx->statements());

  Symbols.popScope();
  DEBUG_EXIT();
  return 0;
}

std::any TypeCheckVisitor::visitExprFunc(AslParser::ExprFuncContext *ctx) {
  DEBUG_ENTER();
  visit(ctx->ident());

  TypesMgr::TypeId tipoFuncion = getTypeDecor(ctx->ident());
  uint numeroParametros = ctx->expr().size();

  for (uint i = 0; i < numeroParametros; ++i) {
    visit(ctx->expr(i));
  }

  bool isCallable = true;
  bool isVoidButExpr = false;

  if (Types.isErrorTy(tipoFuncion)) {
    isCallable = false;
  } else if (not Types.isFunctionTy(tipoFuncion)) {
    Errors.isNotCallable(ctx->ident());
    isCallable = false;
  } else if (Types.isVoidFunction(tipoFuncion)) {
    Errors.isNotFunction(ctx->ident());
    isVoidButExpr = true;
  }

  if (!isCallable) {
    putTypeDecor(ctx, Types.createErrorTy());
    putIsLValueDecor(ctx, false);
    return 0;
  }

  auto tiposParametros = Types.getFuncParamsTypes(tipoFuncion);

  if (numeroParametros != Types.getNumOfParameters(tipoFuncion)) {
    Errors.numberOfParameters(ctx->ident());
    putTypeDecor(ctx, Types.createErrorTy());
    putIsLValueDecor(ctx, false);
    return 0;
  }

  for (uint i = 0; i < numeroParametros; ++i) {
    TypesMgr::TypeId tipoParametro = getTypeDecor(ctx->expr(i));
    if (Types.isErrorTy(tipoParametro)) {
      continue;
    }

    if (not Types.copyableTypes(tiposParametros[i], tipoParametro)) {
      Errors.incompatibleParameter(ctx->expr(i), i + 1, ctx);
    }
  }

  if (isVoidButExpr) {
    putTypeDecor(ctx, Types.createErrorTy());
  } else {
    TypesMgr::TypeId tipoIdentificador = Types.getFuncReturnType(tipoFuncion);
    putTypeDecor(ctx, tipoIdentificador);
  }

  putIsLValueDecor(ctx, false);
  DEBUG_EXIT();
  return 0;
}

std::any TypeCheckVisitor::visitReturnStmt(AslParser::ReturnStmtContext *ctx) {
  DEBUG_ENTER();
  TypesMgr::TypeId currentFunctionType = getCurrentFunctionTy();

  if (not ctx->expr()) {
    if (not Types.isVoidTy(currentFunctionType))
      Errors.incompatibleReturn(ctx->RETURN());
    return 0;
  }

  visit(ctx->expr());
  TypesMgr::TypeId actualReturnType = getTypeDecor(ctx->expr());

  // Use else if to prevent double-printing the error!
  if (Types.isVoidTy(currentFunctionType)) {
    Errors.incompatibleReturn(ctx->RETURN());
  } else if (not Types.isErrorTy(actualReturnType) and
             not Types.copyableTypes(currentFunctionType, actualReturnType)) {
    Errors.incompatibleReturn(ctx->RETURN());
  }

  DEBUG_EXIT();
  return 0;
}

// std::any TypeCheckVisitor::visitDeclarations(AslParser::DeclarationsContext
// *ctx) {
//   DEBUG_ENTER();
//   std::any r = visitChildren(ctx);
//   DEBUG_EXIT();
//   return r;
// }

// std::any TypeCheckVisitor::visitVariable_decl(AslParser::Variable_declContext
// *ctx) {
//   DEBUG_ENTER();
//   std::any r = visitChildren(ctx);
//   DEBUG_EXIT();
//   return r;
// }

// std::any TypeCheckVisitor::visitType(AslParser::TypeContext *ctx) {
//   DEBUG_ENTER();
//   std::any r = visitChildren(ctx);
//   DEBUG_EXIT();
//   return r;
// }

std::any TypeCheckVisitor::visitStatements(AslParser::StatementsContext *ctx) {
  DEBUG_ENTER();
  visitChildren(ctx);
  DEBUG_EXIT();
  return 0;
}

std::any TypeCheckVisitor::visitAssignStmt(AslParser::AssignStmtContext *ctx) {
  DEBUG_ENTER();
  visit(ctx->left_expr());
  visit(ctx->expr());
  TypesMgr::TypeId t1 = getTypeDecor(ctx->left_expr());
  TypesMgr::TypeId t2 = getTypeDecor(ctx->expr());
  if ((not Types.isErrorTy(t1)) and (not Types.isErrorTy(t2)) and
      (not Types.copyableTypes(t1, t2)))
    Errors.incompatibleAssignment(ctx->ASSIGN());
  if ((not Types.isErrorTy(t1)) and (not getIsLValueDecor(ctx->left_expr())))
    Errors.nonReferenceableLeftExpr(ctx->left_expr());
  DEBUG_EXIT();
  return 0;
}

std::any TypeCheckVisitor::visitIfStmt(AslParser::IfStmtContext *ctx) {
  DEBUG_ENTER();
  visit(ctx->expr());
  TypesMgr::TypeId t1 = getTypeDecor(ctx->expr());
  if ((not Types.isErrorTy(t1)) and (not Types.isBooleanTy(t1)))
    Errors.booleanRequired(ctx);
  visit(ctx->statements(0));
  if (ctx->statements().size() > 1) {
    visit(ctx->statements(1));
  }
  DEBUG_EXIT();
  return 0;
}

std::any TypeCheckVisitor::visitWhileStmt(AslParser::WhileStmtContext *ctx) {
  DEBUG_ENTER();
  visit(ctx->expr());
  TypesMgr::TypeId t1 = getTypeDecor(ctx->expr());
  if ((not Types.isErrorTy(t1)) and (not Types.isBooleanTy(t1)))
    Errors.booleanRequired(ctx);
  visit(ctx->statements());
  DEBUG_EXIT();
  return 0;
}

std::any TypeCheckVisitor::visitProcCall(AslParser::ProcCallContext *ctx) {
  DEBUG_ENTER();
  visit(ctx->ident());
  TypesMgr::TypeId t1 = getTypeDecor(ctx->ident());

  uint numeroParametros = ctx->expr().size();

  for (uint i = 0; i < numeroParametros; ++i) {
    visit(ctx->expr(i));
  }

  if (Types.isErrorTy(t1)) {
    return 0;
  }

  if (not Types.isFunctionTy(t1)) {
    Errors.isNotCallable(ctx->ident());
    return 0;
  }

  auto tiposParametros = Types.getFuncParamsTypes(t1);

  if (numeroParametros != Types.getNumOfParameters(t1)) {
    Errors.numberOfParameters(ctx->ident());
    return 0;
  }

  for (uint i = 0; i < numeroParametros; ++i) {
    TypesMgr::TypeId tipoParametro = getTypeDecor(ctx->expr(i));
    if (Types.isErrorTy(tipoParametro)) {
      continue;
    }

    if (not Types.copyableTypes(tiposParametros[i], tipoParametro)) {
      Errors.incompatibleParameter(ctx->expr(i), i + 1, ctx);
    }
  }

  DEBUG_EXIT();
  return 0;
}

std::any TypeCheckVisitor::visitReadStmt(AslParser::ReadStmtContext *ctx) {
  DEBUG_ENTER();
  visit(ctx->left_expr());
  TypesMgr::TypeId t1 = getTypeDecor(ctx->left_expr());
  if ((not Types.isErrorTy(t1)) and (not Types.isPrimitiveTy(t1)) and
      (not Types.isFunctionTy(t1)))
    Errors.readWriteRequireBasic(ctx);
  if ((not Types.isErrorTy(t1)) and (not getIsLValueDecor(ctx->left_expr())))
    Errors.nonReferenceableExpression(ctx);
  DEBUG_EXIT();
  return 0;
}

std::any TypeCheckVisitor::visitWriteExpr(AslParser::WriteExprContext *ctx) {
  DEBUG_ENTER();
  visit(ctx->expr());
  TypesMgr::TypeId t1 = getTypeDecor(ctx->expr());
  if ((not Types.isErrorTy(t1)) and (not Types.isPrimitiveTy(t1)))
    Errors.readWriteRequireBasic(ctx);
  DEBUG_EXIT();
  return 0;
}

// std::any TypeCheckVisitor::visitWriteString(AslParser::WriteStringContext
// *ctx) {
//   DEBUG_ENTER();
//   std::any r = visitChildren(ctx);
//   DEBUG_EXIT();
//   return r;
// }

std::any TypeCheckVisitor::visitLeft_expr(AslParser::Left_exprContext *ctx) {
  DEBUG_ENTER();
  visit(ctx->ident());
  TypesMgr::TypeId t = getTypeDecor(ctx->ident());
  if (ctx->expr()) {
    if ((not Types.isErrorTy(t)) and (not Types.isArrayTy(t))) {
      Errors.nonArrayInArrayAccess(ctx);
      t = Types.createErrorTy();
    }
    visit(ctx->expr());
    TypesMgr::TypeId t2 = getTypeDecor(ctx->expr());
    if ((not Types.isErrorTy(t2)) and (not Types.isIntegerTy(t2))) {
      Errors.nonIntegerIndexInArrayAccess(ctx->expr());
      t = Types.createErrorTy();
    }
    if (Types.isArrayTy(t)) {
      t = Types.getArrayElemType(t);
    }
  }
  putTypeDecor(ctx, t);
  bool b = getIsLValueDecor(ctx->ident());
  putIsLValueDecor(ctx, b);
  DEBUG_EXIT();
  return 0;
}

std::any TypeCheckVisitor::visitArrayAccessExpr(
    AslParser::ArrayAccessExprContext *ctx) {
  DEBUG_ENTER();
  visit(ctx->ident());
  TypesMgr::TypeId t1 = getTypeDecor(ctx->ident());
  if ((not Types.isErrorTy(t1)) and (not Types.isArrayTy(t1))) {
    Errors.nonArrayInArrayAccess(ctx);
    t1 = Types.createErrorTy();
  }
  if (Types.isArrayTy(t1)) {
    t1 = Types.getArrayElemType(t1);
  }

  visit(ctx->expr());
  TypesMgr::TypeId t2 = getTypeDecor(ctx->expr());
  if ((not Types.isErrorTy(t2)) and (not Types.isIntegerTy(t2))) {
    Errors.nonIntegerIndexInArrayAccess(ctx->expr());
  }
  putTypeDecor(ctx, t1);
  putIsLValueDecor(ctx, false);

  DEBUG_EXIT();
  return 0;
}

std::any TypeCheckVisitor::visitArithmetic(AslParser::ArithmeticContext *ctx) {
  DEBUG_ENTER();
  visit(ctx->expr(0));
  TypesMgr::TypeId t1 = getTypeDecor(ctx->expr(0));
  visit(ctx->expr(1));
  TypesMgr::TypeId t2 = getTypeDecor(ctx->expr(1));

  TypesMgr::TypeId t;
  std::string opString = ctx->op->getText();

  if (opString == "%") {
    // Exige estrictamente enteros
    if ((not Types.isErrorTy(t1) and not Types.isIntegerTy(t1)) or
        (not Types.isErrorTy(t2) and not Types.isIntegerTy(t2))) {
      Errors.incompatibleOperator(ctx->op);
    }
    // El resultado de un % siempre se evalúa como int
    t = Types.createIntegerTy();
  }
  // 2. Caso para el resto de operadores aritméticos (+, -, *, /)
  else {
    // Exige que sean numéricos (int o float)
    if (((not Types.isErrorTy(t1)) and (not Types.isNumericTy(t1))) or
        ((not Types.isErrorTy(t2)) and (not Types.isNumericTy(t2)))) {
      Errors.incompatibleOperator(ctx->op);
    }

    if (Types.isFloatTy(t1) or Types.isFloatTy(t2)) {
      t = Types.createFloatTy();
    } else {
      t = Types.createIntegerTy();
    }
  }

  putTypeDecor(ctx, t);
  putIsLValueDecor(ctx, false);
  DEBUG_EXIT();
  return 0;
}

std::any TypeCheckVisitor::visitParenthesis(
    AslParser::ParenthesisContext *ctx) {
  DEBUG_ENTER();
  visit(ctx->expr());
  TypesMgr::TypeId t1 = getTypeDecor(ctx->expr());
  putTypeDecor(ctx, t1);
  putIsLValueDecor(ctx, false);
  DEBUG_EXIT();
  return 0;
}

std::any TypeCheckVisitor::visitNot(AslParser::NotContext *ctx) {
  DEBUG_ENTER();
  visit(ctx->expr());
  TypesMgr::TypeId t = getTypeDecor(ctx->expr());
  if ((not Types.isErrorTy(t)) and (not Types.isBooleanTy(t)))
    Errors.incompatibleOperator(ctx->op);
  TypesMgr::TypeId t1 = Types.createBooleanTy();
  putTypeDecor(ctx, t1);
  putIsLValueDecor(ctx, false);
  DEBUG_EXIT();
  return 0;
}

std::any TypeCheckVisitor::visitLogicalAnd(AslParser::LogicalAndContext *ctx) {
  DEBUG_ENTER();
  visit(ctx->expr(0));
  TypesMgr::TypeId t1 = getTypeDecor(ctx->expr(0));
  visit(ctx->expr(1));
  TypesMgr::TypeId t2 = getTypeDecor(ctx->expr(1));
  if ((not Types.isErrorTy(t1)) and (not Types.isBooleanTy(t1)))
    Errors.incompatibleOperator(ctx->op);
  else if ((not Types.isErrorTy(t2)) and (not Types.isBooleanTy(t2)))
    Errors.incompatibleOperator(ctx->op);
  TypesMgr::TypeId t = Types.createBooleanTy();
  putTypeDecor(ctx, t);
  putIsLValueDecor(ctx, false);
  DEBUG_EXIT();
  return 0;
}

std::any TypeCheckVisitor::visitLogicalOr(AslParser::LogicalOrContext *ctx) {
  DEBUG_ENTER();
  visit(ctx->expr(0));
  TypesMgr::TypeId t1 = getTypeDecor(ctx->expr(0));
  visit(ctx->expr(1));
  TypesMgr::TypeId t2 = getTypeDecor(ctx->expr(1));
  if ((not Types.isErrorTy(t1)) and (not Types.isBooleanTy(t1)))
    Errors.incompatibleOperator(ctx->op);
  if ((not Types.isErrorTy(t2)) and (not Types.isBooleanTy(t2)))
    Errors.incompatibleOperator(ctx->op);
  TypesMgr::TypeId t = Types.createBooleanTy();
  putTypeDecor(ctx, t);
  putIsLValueDecor(ctx, false);
  DEBUG_EXIT();
  return 0;
}

std::any TypeCheckVisitor::visitRelational(AslParser::RelationalContext *ctx) {
  DEBUG_ENTER();
  visit(ctx->expr(0));
  TypesMgr::TypeId t1 = getTypeDecor(ctx->expr(0));
  visit(ctx->expr(1));
  TypesMgr::TypeId t2 = getTypeDecor(ctx->expr(1));
  std::string oper = ctx->op->getText();
  if ((not Types.isErrorTy(t1)) and (not Types.isErrorTy(t2)) and
      (not Types.comparableTypes(t1, t2, oper)))
    Errors.incompatibleOperator(ctx->op);
  TypesMgr::TypeId t = Types.createBooleanTy();
  putTypeDecor(ctx, t);
  putIsLValueDecor(ctx, false);
  DEBUG_EXIT();
  return 0;
}

// Esta funcion tendra problemas cuando tocara diferenciar un boleano = 1 con un
// int = 1
std::any TypeCheckVisitor::visitValue(AslParser::ValueContext *ctx) {
  DEBUG_ENTER();
  TypesMgr::TypeId t;
  std::string str = ctx->val->getText();
  if (str.front() == '\'' && str.back() == '\'') {
    t = Types.createCharacterTy();
  } else if (str.find('.') != std::string::npos) {
    t = Types.createFloatTy();
  } else if (str == "true" or str == "false") {
    t = Types.createBooleanTy();
  } else {
    t = Types.createIntegerTy();
  }
  putTypeDecor(ctx, t);
  putIsLValueDecor(ctx, false);
  DEBUG_EXIT();
  return 0;
}

std::any TypeCheckVisitor::visitExprIdent(AslParser::ExprIdentContext *ctx) {
  DEBUG_ENTER();
  visit(ctx->ident());
  TypesMgr::TypeId t1 = getTypeDecor(ctx->ident());
  putTypeDecor(ctx, t1);
  bool b = getIsLValueDecor(ctx->ident());
  putIsLValueDecor(ctx, b);
  DEBUG_EXIT();
  return 0;
}

std::any TypeCheckVisitor::visitUnaryOperator(AslParser::UnaryOperatorContext *ctx) {
  DEBUG_ENTER();
  visit(ctx->expr());
  TypesMgr::TypeId t1 = getTypeDecor(ctx->expr());
  if ((not Types.isErrorTy(t1)) and (not Types.isNumericTy(t1))) {
    Errors.incompatibleOperator(ctx->op);
    putTypeDecor(ctx, Types.createErrorTy());

  } else {
    putTypeDecor(ctx, t1);
  }

  putIsLValueDecor(ctx, false);
  DEBUG_EXIT();
  return 0;
}

std::any TypeCheckVisitor::visitIdent(AslParser::IdentContext *ctx) {
  DEBUG_ENTER();
  std::string ident = ctx->getText();
  if (Symbols.findInStack(ident) == -1) {
    Errors.undeclaredIdent(ctx->ID());
    TypesMgr::TypeId te = Types.createErrorTy();
    putTypeDecor(ctx, te);
    putIsLValueDecor(ctx, true);
  } else {
    TypesMgr::TypeId t1 = Symbols.getType(ident);
    putTypeDecor(ctx, t1);
    if (Symbols.isFunctionClass(ident))
      putIsLValueDecor(ctx, false);
    else
      putIsLValueDecor(ctx, true);
  }
  DEBUG_EXIT();
  return 0;
}

// Getters for the necessary tree node atributes:
//   Scope, Type ans IsLValue
SymTable::ScopeId TypeCheckVisitor::getScopeDecor(
    antlr4::ParserRuleContext *ctx) {
  return Decorations.getScope(ctx);
}
TypesMgr::TypeId TypeCheckVisitor::getTypeDecor(
    antlr4::ParserRuleContext *ctx) {
  return Decorations.getType(ctx);
}
bool TypeCheckVisitor::getIsLValueDecor(antlr4::ParserRuleContext *ctx) {
  return Decorations.getIsLValue(ctx);
}

// Setters for the necessary tree node attributes:
//   Scope, Type ans IsLValue
void TypeCheckVisitor::putScopeDecor(antlr4::ParserRuleContext *ctx,
                                     SymTable::ScopeId s) {
  Decorations.putScope(ctx, s);
}
void TypeCheckVisitor::putTypeDecor(antlr4::ParserRuleContext *ctx,
                                    TypesMgr::TypeId t) {
  Decorations.putType(ctx, t);
}
void TypeCheckVisitor::putIsLValueDecor(antlr4::ParserRuleContext *ctx,
                                        bool b) {
  Decorations.putIsLValue(ctx, b);
}
