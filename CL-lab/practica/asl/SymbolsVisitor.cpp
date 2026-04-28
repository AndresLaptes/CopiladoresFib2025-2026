//////////////////////////////////////////////////////////////////////
//
//    SymbolsVisitor - Walk the parser tree to register symbols
//                     for the Asl programming language
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

#include "SymbolsVisitor.h"

#include <cstddef> // std::size_t
#include <iostream>
#include <string>
#include <vector>

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
SymbolsVisitor::SymbolsVisitor(TypesMgr &Types, SymTable &Symbols,
                               TreeDecoration &Decorations, SemErrors &Errors)
    : Types{Types}, Symbols{Symbols}, Decorations{Decorations}, Errors{Errors} {
}

// Methods to visit each kind of node:
//
std::any SymbolsVisitor::visitProgram(AslParser::ProgramContext *ctx) {
    DEBUG_ENTER();
    SymTable::ScopeId sc = Symbols.pushNewScope(SymTable::GLOBAL_SCOPE_NAME);
    putScopeDecor(ctx, sc);
    for (auto ctxFunc : ctx->function())
        visit(ctxFunc);
    Symbols.popScope();
    DEBUG_EXIT();
    return 0;
}

std::any SymbolsVisitor::visitFunction(AslParser::FunctionContext *ctx) {
    DEBUG_ENTER();
    std::string funcName = ctx->ID()->getText();
    SymTable::ScopeId sc = Symbols.pushNewScope(funcName);
    putScopeDecor(ctx, sc);

    if (ctx->funParDeclaration())
        visit(ctx->funParDeclaration());

    visit(ctx->declarations());
    visit(ctx->statements()); // May be unnecessary
    if (ctx->type())
        visit(ctx->type());
    Symbols.popScope();

    if (Symbols.findInCurrentScope(funcName))
        Errors.declaredIdent(ctx->ID());
    else {
        std::vector<TypesMgr::TypeId> lParamsTy;
        if (ctx->funParDeclaration()) {
            auto paramsCtx =
                dynamic_cast<AslParser::ParametrosFuncionContext *>(
                    ctx->funParDeclaration());
            if (paramsCtx)
                for (auto tyCtx : paramsCtx->type())
                    lParamsTy.push_back(getTypeDecor(tyCtx));
        }

        TypesMgr::TypeId tRet = Types.createVoidTy();
        if (ctx->type()) {
            tRet = getTypeDecor(ctx->type());
        } else {
            tRet = Types.createVoidTy();
        }

        TypesMgr::TypeId tFunc = Types.createFunctionTy(lParamsTy, tRet);
        Symbols.addFunction(funcName, tFunc);
    }
    DEBUG_EXIT();
    return 0;
}

std::any SymbolsVisitor::visitParametrosFuncion(
    AslParser::ParametrosFuncionContext *ctx) {
    DEBUG_ENTER();

    for (std::size_t i = 0; i < ctx->ID().size(); ++i) {

        visit(ctx->type(i));
        TypesMgr::TypeId type = getTypeDecor(ctx->type(i));
        std::string name = ctx->ID(i)->getText();

        if (Symbols.findInCurrentScope(name))
            Errors.declaredIdent(ctx->ID(i));
        else
            Symbols.addLocalVar(name, type);
    }

    DEBUG_EXIT();
    return 0;
}

std::any
SymbolsVisitor::visitDeclarations(AslParser::DeclarationsContext *ctx) {
    DEBUG_ENTER();
    visitChildren(ctx);
    DEBUG_EXIT();
    return 0;
}

std::any
SymbolsVisitor::visitVariable_decl(AslParser::Variable_declContext *ctx) {
    DEBUG_ENTER();
    visit(ctx->type());
    TypesMgr::TypeId t = getTypeDecor(ctx->type());

    for (auto idToken : ctx->ID()) {
        std::string name = idToken->getText();
        if (Symbols.findInCurrentScope(name))
            Errors.declaredIdent(idToken);
        else
            Symbols.addLocalVar(name, t);
    }

    DEBUG_EXIT();
    return 0;
}

std::any SymbolsVisitor::visitTypeBasic(AslParser::TypeBasicContext *ctx) {
    DEBUG_ENTER();
    visit(ctx->basicType());
    putTypeDecor(ctx, getTypeDecor(ctx->basicType()));
    DEBUG_EXIT();
    return 0;
}

std::any SymbolsVisitor::visitArrayType(AslParser::ArrayTypeContext *ctx) {
    DEBUG_ENTER();
    visit(ctx->basicType());
    std::size_t size = std::stoul(ctx->INTVAL()->getText());
    TypesMgr::TypeId tElem = getTypeDecor(ctx->basicType());
    TypesMgr::TypeId tArray = Types.createArrayTy(size, tElem);
    putTypeDecor(ctx, tArray);
    DEBUG_EXIT();
    return 0;
}

std::any SymbolsVisitor::visitBasicType(AslParser::BasicTypeContext *ctx) {
    DEBUG_ENTER();
    TypesMgr::TypeId t;
    if (ctx->INT())
        t = Types.createIntegerTy();
    else if (ctx->BOOL())
        t = Types.createBooleanTy();
    else if (ctx->CHAR())
        t = Types.createCharacterTy();
    else if (ctx->FLOAT())
        t = Types.createFloatTy();
    putTypeDecor(ctx, t);
    DEBUG_EXIT();
    return 0;
}

// std::any SymbolsVisitor::visitStatements(AslParser::StatementsContext *ctx) {
//   DEBUG_ENTER();
//   std::any r = visitChildren(ctx);
//   DEBUG_EXIT();
//   return r;
// }

// std::any SymbolsVisitor::visitAssignStmt(AslParser::AssignStmtContext *ctx) {
//   DEBUG_ENTER();
//   std::any r = visitChildren(ctx);
//   DEBUG_EXIT();
//   return r;
// }

// std::any SymbolsVisitor::visitIfStmt(AslParser::IfStmtContext *ctx) {
//   DEBUG_ENTER();
//   std::any r = visitChildren(ctx);
//   DEBUG_EXIT();
//   return r;
// }

// std::any SymbolsVisitor::visitProcCall(AslParser::ProcCallContext *ctx) {
//   DEBUG_ENTER();
//   std::any r = visitChildren(ctx);
//   DEBUG_EXIT();
//   return r;
// }

// std::any SymbolsVisitor::visitReadStmt(AslParser::ReadStmtContext *ctx) {
//   DEBUG_ENTER();
//   std::any r = visitChildren(ctx);
//   DEBUG_EXIT();
//   return r;
// }

// std::any SymbolsVisitor::visitWriteExpr(AslParser::WriteExprContext *ctx) {
//   DEBUG_ENTER();
//   std::any r = visitChildren(ctx);
//   DEBUG_EXIT();
//   return r;
// }

// std::any SymbolsVisitor::visitWriteString(AslParser::WriteStringContext *ctx)
// {
//   DEBUG_ENTER();
//   std::any r = visitChildren(ctx);
//   DEBUG_EXIT();
//   return r;
// }

// std::any SymbolsVisitor::visitLeft_expr(AslParser::Left_exprContext *ctx) {
//   DEBUG_ENTER();
//   std::any r = visitChildren(ctx);
//   DEBUG_EXIT();
//   return r;
// }

// std::any SymbolsVisitor::visitExprIdent(AslParser::ExprIdentContext *ctx) {
//   DEBUG_ENTER();
//   std::any r = visitChildren(ctx);
//   DEBUG_EXIT();
//   return r;
// }

// std::any SymbolsVisitor::visitArithmetic(AslParser::ArithmeticContext *ctx) {
//   DEBUG_ENTER();
//   std::any r = visitChildren(ctx);
//   DEBUG_EXIT();
//   return r;
// }

// std::any SymbolsVisitor::visitRelational(AslParser::RelationalContext *ctx) {
//   DEBUG_ENTER();
//   std::any r = visitChildren(ctx);
//   DEBUG_EXIT();
//   return r;
// }

// std::any SymbolsVisitor::visitValue(AslParser::ValueContext *ctx) {
//   DEBUG_ENTER();
//   std::any r = visitChildren(ctx);
//   DEBUG_EXIT();
//   return r;
// }

// std::any SymbolsVisitor::visitIdent(AslParser::IdentContext *ctx) {
//   DEBUG_ENTER();
//   std::any r = visitChildren(ctx);
//   DEBUG_EXIT();
//   return r;
// }

// Getters for the necessary tree node atributes:
//   Scope and Type
SymTable::ScopeId
SymbolsVisitor::getScopeDecor(antlr4::ParserRuleContext *ctx) {
    return Decorations.getScope(ctx);
}
TypesMgr::TypeId SymbolsVisitor::getTypeDecor(antlr4::ParserRuleContext *ctx) {
    return Decorations.getType(ctx);
}

// Setters for the necessary tree node attributes:
//   Scope and Type
void SymbolsVisitor::putScopeDecor(antlr4::ParserRuleContext *ctx,
                                   SymTable::ScopeId s) {
    Decorations.putScope(ctx, s);
}
void SymbolsVisitor::putTypeDecor(antlr4::ParserRuleContext *ctx,
                                  TypesMgr::TypeId t) {
    Decorations.putType(ctx, t);
}
