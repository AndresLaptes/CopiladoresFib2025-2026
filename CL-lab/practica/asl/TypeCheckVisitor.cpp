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
    : Types{Types}, Symbols{Symbols}, Decorations{Decorations}, Errors{Errors} {
}

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

    for (auto ctxFunc : ctx->function()) visit(ctxFunc);
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
    TypesMgr::TypeId retTy = Types.createVoidTy();
    if (ctx->type()) {
        visit(ctx->type());
        retTy = getTypeDecor(ctx->type());
    }

    setCurrentFunctionTy(retTy);

    if (ctx->funParDeclaration()) visit(ctx->funParDeclaration());


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
        DEBUG_EXIT();
        return 0;
    }

    auto tiposParametros = Types.getFuncParamsTypes(tipoFuncion);

    if (numeroParametros != Types.getNumOfParameters(tipoFuncion)) {
        Errors.numberOfParameters(ctx->ident());
        putTypeDecor(ctx, Types.createErrorTy());
        putIsLValueDecor(ctx, false);
        DEBUG_EXIT();
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
        TypesMgr::TypeId tipoIdentificador =
            Types.getFuncReturnType(tipoFuncion);
        putTypeDecor(ctx, tipoIdentificador);
    }

    putIsLValueDecor(ctx, false);
    DEBUG_EXIT();
    return 0;
}

std::any TypeCheckVisitor::visitReturnStmt(AslParser::ReturnStmtContext *ctx) {
    DEBUG_ENTER();
    TypesMgr::TypeId expectedTy = getCurrentFunctionTy();

    if (not ctx->expr()) {
        if (not Types.isVoidTy(expectedTy))
            Errors.incompatibleReturn(ctx->RETURN());
    }
    else {
        visit(ctx->expr());
        TypesMgr::TypeId actualTy = getTypeDecor(ctx->expr());

        if (Types.isVoidTy(expectedTy)) {
            Errors.incompatibleReturn(ctx->RETURN());
        } else if (not Types.isErrorTy(actualTy) and
                not Types.copyableTypes(expectedTy, actualTy)) {
            Errors.incompatibleReturn(ctx->RETURN());
        }
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
    TypesMgr::TypeId tLeft = getTypeDecor(ctx->left_expr());
    TypesMgr::TypeId tRight = getTypeDecor(ctx->expr());
    if ((not Types.isErrorTy(tLeft)) and (not Types.isErrorTy(tRight)) and
        (not Types.copyableTypes(tLeft, tRight)))
        Errors.incompatibleAssignment(ctx->ASSIGN());
    if ((not Types.isErrorTy(tLeft)) and (not getIsLValueDecor(ctx->left_expr())))
        Errors.nonReferenceableLeftExpr(ctx->left_expr());
    DEBUG_EXIT();
    return 0;
}

std::any TypeCheckVisitor::visitIfStmt(AslParser::IfStmtContext *ctx) {
    DEBUG_ENTER();
    visit(ctx->expr());
    TypesMgr::TypeId tCond = getTypeDecor(ctx->expr());
    if ((not Types.isErrorTy(tCond)) and (not Types.isBooleanTy(tCond))) Errors.booleanRequired(ctx);
    visit(ctx->statements(0));
    if (ctx->statements().size() > 1) visit(ctx->statements(1));
    DEBUG_EXIT();
    return 0;
}

std::any TypeCheckVisitor::visitWhileStmt(AslParser::WhileStmtContext *ctx) {
    DEBUG_ENTER();
    visit(ctx->expr());
    TypesMgr::TypeId tCond = getTypeDecor(ctx->expr());
    if ((not Types.isErrorTy(tCond)) and (not Types.isBooleanTy(tCond))) Errors.booleanRequired(ctx);
    visit(ctx->statements());
    DEBUG_EXIT();
    return 0;
}

std::any TypeCheckVisitor::visitProcCall(AslParser::ProcCallContext *ctx) {
    DEBUG_ENTER();
    visit(ctx->ident());
    TypesMgr::TypeId tFunc = getTypeDecor(ctx->ident());

    uint numeroParametros = ctx->expr().size();

    for (auto argCtx: ctx->expr()) visit(argCtx);

    if (Types.isErrorTy(tFunc)) {
        DEBUG_EXIT();
        return 0;
    }

    if (not Types.isFunctionTy(tFunc)) {
        Errors.isNotCallable(ctx->ident());
        DEBUG_EXIT();
        return 0;
    }

    std::size_t numArgs = ctx->expr().size();
    std::size_t numParams = Types.getNumOfParameters(tFunc);
    if (numArgs != numParams) {
        Errors.numberOfParameters(ctx->ident());
        DEBUG_EXIT();
        return 0;
    }

    auto paramTys = Types.getFuncParamsTypes(tFunc);
    for (uint i = 0; i < numArgs; ++i) {
        TypesMgr::TypeId tArg = getTypeDecor(ctx->expr(i));
        if (not Types.isErrorTy(tArg) and not Types.copyableTypes(paramTys[i], tArg)) Errors.incompatibleParameter(ctx->expr(i), i+1, ctx);
    }

    DEBUG_EXIT();
    return 0;
}

std::any TypeCheckVisitor::visitReadStmt(AslParser::ReadStmtContext *ctx) {
    DEBUG_ENTER();
    visit(ctx->left_expr());
    TypesMgr::TypeId t = getTypeDecor(ctx->left_expr());
    if ((not Types.isErrorTy(t)) and (not Types.isPrimitiveTy(t)) and
        (not Types.isFunctionTy(t)))
        Errors.readWriteRequireBasic(ctx);
    if ((not Types.isErrorTy(t)) and (not getIsLValueDecor(ctx->left_expr())))
        Errors.nonReferenceableExpression(ctx);
    DEBUG_EXIT();
    return 0;
}

std::any TypeCheckVisitor::visitWriteExpr(AslParser::WriteExprContext *ctx) {
    DEBUG_ENTER();
    visit(ctx->expr());
    TypesMgr::TypeId t = getTypeDecor(ctx->expr());
    if ((not Types.isErrorTy(t)) and (not Types.isPrimitiveTy(t)))
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

std::any TypeCheckVisitor::visitArrayAccessExpr(AslParser::ArrayAccessExprContext *ctx) {
    DEBUG_ENTER();
    visit(ctx->ident());
    TypesMgr::TypeId tArr = getTypeDecor(ctx->ident());
    if ((not Types.isErrorTy(tArr)) and (not Types.isArrayTy(tArr))) {
        Errors.nonArrayInArrayAccess(ctx);
        tArr = Types.createErrorTy();
    }
    if (Types.isArrayTy(tArr)) {
        tArr = Types.getArrayElemType(tArr);
    }

    visit(ctx->expr());
    TypesMgr::TypeId tElem = getTypeDecor(ctx->expr());
    if ((not Types.isErrorTy(tElem)) and (not Types.isIntegerTy(tElem))) {
        Errors.nonIntegerIndexInArrayAccess(ctx->expr());
    }
    putTypeDecor(ctx, tArr);
    putIsLValueDecor(ctx, false);

    DEBUG_EXIT();
    return 0;
}

std::any TypeCheckVisitor::visitArithmetic(AslParser::ArithmeticContext *ctx) {
    DEBUG_ENTER();
    visit(ctx->expr(0));
    visit(ctx->expr(1));
    TypesMgr::TypeId tLeft = getTypeDecor(ctx->expr(0));
    TypesMgr::TypeId tRight = getTypeDecor(ctx->expr(1));
    TypesMgr::TypeId tResult;

    if (ctx->MOD()) {
        if ((not Types.isErrorTy(tLeft) and not Types.isIntegerTy(tLeft)) or (not Types.isErrorTy(tRight) and not Types.isIntegerTy(tRight))) Errors.incompatibleOperator(ctx->op);
        tResult = Types.createIntegerTy();
    }
    // 2. Caso para el resto de operadores aritméticos (+, -, *, /)
    else {
        // Exige que sean numéricos (int o float)
        if (((not Types.isErrorTy(tLeft)) and (not Types.isNumericTy(tLeft))) or ((not Types.isErrorTy(tRight)) and (not Types.isNumericTy(tRight)))) Errors.incompatibleOperator(ctx->op);

        if (Types.isFloatTy(tLeft) or Types.isFloatTy(tRight)) tResult = Types.createFloatTy();
        else tResult = Types.createIntegerTy();
    }

    putTypeDecor(ctx, tResult);
    putIsLValueDecor(ctx, false);
    DEBUG_EXIT();
    return 0;
}

std::any
TypeCheckVisitor::visitParenthesis(AslParser::ParenthesisContext *ctx) {
    DEBUG_ENTER();
    visit(ctx->expr());
    putTypeDecor(ctx, getTypeDecor(ctx->expr()));
    putIsLValueDecor(ctx, false);
    DEBUG_EXIT();
    return 0;
}

std::any TypeCheckVisitor::visitNot(AslParser::NotContext *ctx) {
    DEBUG_ENTER();
    visit(ctx->expr());
    TypesMgr::TypeId tExpr = getTypeDecor(ctx->expr());
    if ((not Types.isErrorTy(tExpr)) and (not Types.isBooleanTy(tExpr))) Errors.incompatibleOperator(ctx->op);
    putTypeDecor(ctx, Types.createBooleanTy());
    putIsLValueDecor(ctx, false);
    DEBUG_EXIT();
    return 0;
}

std::any TypeCheckVisitor::visitLogicalAnd(AslParser::LogicalAndContext *ctx) {
    DEBUG_ENTER();
    visit(ctx->expr(0));
    TypesMgr::TypeId tLeft = getTypeDecor(ctx->expr(0));
    visit(ctx->expr(1));
    TypesMgr::TypeId tRight = getTypeDecor(ctx->expr(1));
    if ((not Types.isErrorTy(tLeft)) and (not Types.isBooleanTy(tLeft)))
        Errors.incompatibleOperator(ctx->op);
    else if ((not Types.isErrorTy(tRight)) and (not Types.isBooleanTy(tRight)))
        Errors.incompatibleOperator(ctx->op);
    putTypeDecor(ctx, Types.createBooleanTy());
    putIsLValueDecor(ctx, false);
    DEBUG_EXIT();
    return 0;
}

std::any TypeCheckVisitor::visitLogicalOr(AslParser::LogicalOrContext *ctx) {
    DEBUG_ENTER();
    visit(ctx->expr(0));
    TypesMgr::TypeId tLeft = getTypeDecor(ctx->expr(0));
    visit(ctx->expr(1));
    TypesMgr::TypeId tRight = getTypeDecor(ctx->expr(1));
    if ((not Types.isErrorTy(tLeft)) and (not Types.isBooleanTy(tLeft)))
        Errors.incompatibleOperator(ctx->op);
    else if ((not Types.isErrorTy(tRight)) and (not Types.isBooleanTy(tRight)))
        Errors.incompatibleOperator(ctx->op);
    putTypeDecor(ctx, Types.createBooleanTy());
    putIsLValueDecor(ctx, false);
    DEBUG_EXIT();
    return 0;
}

std::any TypeCheckVisitor::visitRelational(AslParser::RelationalContext *ctx) {
    DEBUG_ENTER();
    visit(ctx->expr(0));
    TypesMgr::TypeId tLeft = getTypeDecor(ctx->expr(0));
    visit(ctx->expr(1));
    TypesMgr::TypeId tRight = getTypeDecor(ctx->expr(1));
    std::string op = ctx->op->getText();
    if ((not Types.isErrorTy(tLeft)) and (not Types.isErrorTy(tRight)) and
        (not Types.comparableTypes(tLeft, tRight, op)))
        Errors.incompatibleOperator(ctx->op);
    putTypeDecor(ctx, Types.createBooleanTy());
    putIsLValueDecor(ctx, false);
    DEBUG_EXIT();
    return 0;
}

// Esta funcion tendra problemas cuando tocara diferenciar un boleano = 1 con un
// int = 1
std::any TypeCheckVisitor::visitValue(AslParser::ValueContext *ctx) {
    DEBUG_ENTER();
    TypesMgr::TypeId t;
    if (ctx->CHARVAL()) {
        t = Types.createCharacterTy();
    } else if (ctx->FLOATVAL()) {
        t = Types.createFloatTy();
    } else if (ctx->BOOLVAL()) {
        t = Types.createBooleanTy();
    } else if (ctx->INTVAL()) {
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
    putTypeDecor(ctx, getTypeDecor(ctx->ident()));
    putIsLValueDecor(ctx, getIsLValueDecor(ctx->ident()));
    DEBUG_EXIT();
    return 0;
}

std::any TypeCheckVisitor::visitUnaryOperator(AslParser::UnaryOperatorContext *ctx) {
    DEBUG_ENTER();
    visit(ctx->expr());
    TypesMgr::TypeId tValue = getTypeDecor(ctx->expr());
    if ((not Types.isErrorTy(tValue)) and (not Types.isNumericTy(tValue))) {
        Errors.incompatibleOperator(ctx->op);
        tValue = Types.createErrorTy();
    }
    putTypeDecor(ctx, tValue);
    putIsLValueDecor(ctx, false);
    DEBUG_EXIT();
    return 0;
}

std::any TypeCheckVisitor::visitIdent(AslParser::IdentContext *ctx) {
    DEBUG_ENTER();
    std::string ident = ctx->getText();
    if (Symbols.findInStack(ident) == -1) {
        Errors.undeclaredIdent(ctx->ID());
        putTypeDecor(ctx, Types.createErrorTy());
        putIsLValueDecor(ctx, true);
    } else {
        putTypeDecor(ctx, Symbols.getType(ident));
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
SymTable::ScopeId
TypeCheckVisitor::getScopeDecor(antlr4::ParserRuleContext *ctx) {
    return Decorations.getScope(ctx);
}
TypesMgr::TypeId
TypeCheckVisitor::getTypeDecor(antlr4::ParserRuleContext *ctx) {
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
