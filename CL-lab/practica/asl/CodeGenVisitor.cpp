//////////////////////////////////////////////////////////////////////
//
//    CodeGenVisitor - Walk the parser tree to do
//                     the generation of code
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

#include "CodeGenVisitor.h"

#include <cstddef> // std::size_t
#include <string>

#include "../common/SymTable.h"
#include "../common/TreeDecoration.h"
#include "../common/TypesMgr.h"
#include "../common/code.h"
#include "antlr4-runtime.h"

// uncomment the following line to enable debugging messages with DEBUG*
//  #define DEBUG_BUILD
#include "../common/debug.h"

// using namespace std;

// Constructor
CodeGenVisitor::CodeGenVisitor(TypesMgr &Types, SymTable &Symbols,
                               TreeDecoration &Decorations)
    : Types{Types}, Symbols{Symbols}, Decorations{Decorations} {}

// Accessor/Mutator to the attribute currFunctionType
TypesMgr::TypeId CodeGenVisitor::getCurrentFunctionTy() const {
    return currFunctionType;
}

void CodeGenVisitor::setCurrentFunctionTy(TypesMgr::TypeId type) {
    currFunctionType = type;
}

// Methods to visit each kind of node:
//
std::any CodeGenVisitor::visitProgram(AslParser::ProgramContext *ctx) {
    DEBUG_ENTER();
    code my_code;
    SymTable::ScopeId sc = getScopeDecor(ctx);
    Symbols.pushThisScope(sc);
    for (auto ctxFunc : ctx->function()) {
        subroutine subr = std::any_cast<subroutine>(visit(ctxFunc));
        my_code.add_subroutine(subr);
    }
    Symbols.popScope();
    DEBUG_EXIT();
    return my_code;
}

std::any CodeGenVisitor::visitParametrosFuncion(
    AslParser::ParametrosFuncionContext *ctx) {
    DEBUG_ENTER();

    uint numParams = ctx->ID().size();
    std::vector<var> vars;
    for (uint i = 0; i < numParams; ++i) {
        TypesMgr::TypeId t1 = getTypeDecor(ctx->type(i));
        std::string paramTy = Types.to_string_basic(t1);
        vars.push_back(var{ctx->ID(i)->getText(), paramTy});
    }

    DEBUG_EXIT();
    return vars;
}

std::any CodeGenVisitor::visitReturnStmt(AslParser::ReturnStmtContext *ctx) {
    DEBUG_ENTER();
    instructionList code;
    if (ctx->expr()) {
        CodeAttribs &&codeAtrsExpr =
            std::any_cast<CodeAttribs>(visit(ctx->expr()));
        code = codeAtrsExpr.code;
        code = code || instruction::LOAD("_result", codeAtrsExpr.addr);
    }

    code = code || instruction::RETURN();

    DEBUG_EXIT();
    return code;
}

std::any CodeGenVisitor::visitFunction(AslParser::FunctionContext *ctx) {
    DEBUG_ENTER();
    SymTable::ScopeId sc = getScopeDecor(ctx);
    Symbols.pushThisScope(sc);
    subroutine subr(ctx->ID()->getText());
    codeCounters.reset();
    if (ctx->type()) {
        TypesMgr::TypeId retType = getTypeDecor(ctx->type());
        setCurrentFunctionTy(retType);
        // std::size_t size = Types.getSizeOfType(retType);
        subr.add_param("_result", Types.to_string(retType), false);
    }

    if (ctx->funParDeclaration()) {
        AslParser::ParametrosFuncionContext *parCtx =
            dynamic_cast<AslParser::ParametrosFuncionContext *>(
                ctx->funParDeclaration());
        uint numParams = parCtx->ID().size();
        for (uint i = 0; i < numParams; ++i) {
            TypesMgr::TypeId t1 = getTypeDecor(parCtx->type(i));
            bool isArray = Types.isArrayTy(t1);
            subr.add_param(parCtx->ID(i)->getText(), Types.to_string_basic(t1),
                           isArray);
        }
    }
    std::vector<var> &&lvars =
        std::any_cast<std::vector<var>>(visit(ctx->declarations()));
    for (auto &onevar : lvars) {
        subr.add_var(onevar);
    }
    instructionList &&code =
        std::any_cast<instructionList>(visit(ctx->statements()));
    if (!ctx->type()) {
        code = code || instruction::RETURN();
    }
    subr.set_instructions(code);
    Symbols.popScope();
    DEBUG_EXIT();
    return subr;
}

std::any
CodeGenVisitor::visitDeclarations(AslParser::DeclarationsContext *ctx) {
    DEBUG_ENTER();
    std::vector<var> lvars;

    for (auto &varDeclCtx : ctx->variable_decl()) {
        std::vector<var> declVars =
            std::any_cast<std::vector<var>>(visit(varDeclCtx));

        lvars.insert(lvars.end(), declVars.begin(), declVars.end());
    }

    DEBUG_EXIT();
    return lvars;
}

std::any
CodeGenVisitor::visitVariable_decl(AslParser::Variable_declContext *ctx) {
    DEBUG_ENTER();
    TypesMgr::TypeId t1 = getTypeDecor(ctx->type());
    std::string varTy = Types.to_string_basic(t1);
    std::size_t size = 1;
    if (Types.isArrayTy(t1))
        size = Types.getArraySize(t1);

    std::vector<var> vars;

    for (auto idToken : ctx->ID()) {
        vars.push_back(var{idToken->getText(), varTy, size});
    }

    DEBUG_EXIT();
    return vars;
}

std::any CodeGenVisitor::visitStatements(AslParser::StatementsContext *ctx) {
    DEBUG_ENTER();
    instructionList code;
    for (auto stCtx : ctx->statement()) {
        instructionList &&codeS = std::any_cast<instructionList>(visit(stCtx));
        code = code || codeS;
    }
    DEBUG_EXIT();
    return code;
}

std::any CodeGenVisitor::visitAssignStmt(AslParser::AssignStmtContext *ctx) {
    DEBUG_ENTER();
    instructionList code;

    CodeAttribs codAtsE1 = std::any_cast<CodeAttribs>(visit(ctx->left_expr()));
    std::string addr1 = codAtsE1.addr;
    std::string offs1 = codAtsE1.offs;
    instructionList code1 = codAtsE1.code;

    CodeAttribs codAtsE2 = std::any_cast<CodeAttribs>(visit(ctx->expr()));
    std::string addr2 = codAtsE2.addr;
    instructionList code2 = codAtsE2.code;

    if (offs1 != "") {
        // Si hay offset, es una escritura en array: addr1[offs1] = addr2
        code = code1 || code2 || instruction::XLOAD(addr1, offs1, addr2);
    } else {
        // Si el offset está vacío, es una asignación normal: addr1 = addr2
        code = code1 || code2 || instruction::LOAD(addr1, addr2);
    }

    DEBUG_EXIT();
    return code;
}

std::any CodeGenVisitor::visitIfStmt(AslParser::IfStmtContext *ctx) {
    DEBUG_ENTER();
    instructionList code;
    CodeAttribs codAtsE = std::any_cast<CodeAttribs>(visit(ctx->expr()));
    std::string addr1 = codAtsE.addr;
    instructionList code1 = codAtsE.code;
    instructionList code2 =
        std::any_cast<instructionList>(visit(ctx->statements(0)));

    std::string label = codeCounters.newLabelIF();
    std::string labelEndIf = "endif" + label;

    if (ctx->statements().size() > 1) {
        instructionList code3 =
            std::any_cast<instructionList>(visit(ctx->statements(1)));
        std::string labelElse = "else" + label;

        code = code1 || instruction::FJUMP(addr1, labelElse) || code2 ||
               instruction::UJUMP(labelEndIf) ||
               instruction::LABEL(labelElse) || code3 ||
               instruction::LABEL(labelEndIf);
    } else {
        code = code1 || instruction::FJUMP(addr1, labelEndIf) || code2 ||
               instruction::LABEL(labelEndIf);
    }

    DEBUG_EXIT();
    return code;
}

std::any CodeGenVisitor::visitProcCall(AslParser::ProcCallContext *ctx) {
    DEBUG_ENTER();
    instructionList code;
    std::string name = ctx->ident()->getText();
    TypesMgr::TypeId tFunc = Symbols.getType(name);
    bool hasReturnValue =
        Types.isFunctionTy(tFunc) && (not Types.isVoidFunction(tFunc));
    std::vector<TypesMgr::TypeId> paramTypes;
    if (Types.isFunctionTy(tFunc))
        paramTypes = Types.getFuncParamsTypes(tFunc);

    if (hasReturnValue) {
        code = code || instruction::PUSH();
    }

    for (std::size_t i = 0; i < ctx->expr().size(); ++i) {
        auto exprCtx = ctx->expr(i);
        CodeAttribs &&codAt = std::any_cast<CodeAttribs>(visit(exprCtx));
        code = code || codAt.code;

        std::string argAddr = codAt.addr;
        TypesMgr::TypeId tArg = getTypeDecor(exprCtx);
        if (i < paramTypes.size() and Types.isFloatTy(paramTypes[i]) and
            Types.isIntegerTy(tArg)) {
            std::string tmpFloat = "%" + codeCounters.newTEMP();
            code = code || instruction::FLOAT(tmpFloat, argAddr);
            argAddr = tmpFloat;
        }

        code = code || instruction::PUSH(argAddr);
    }

    code = code || instruction::CALL(name);

    for (std::size_t i = 0; i < ctx->expr().size(); ++i) {
        code = code || instruction::POP();
    }
    if (hasReturnValue) {
        code = code || instruction::POP();
    }
    DEBUG_EXIT();
    return code;
}

std::any CodeGenVisitor::visitExprFunc(AslParser::ExprFuncContext *ctx) {
    DEBUG_ENTER();
    instructionList code;
    std::string name = ctx->ident()->getText();
    TypesMgr::TypeId tFunc = Symbols.getType(name);
    std::vector<TypesMgr::TypeId> paramTypes;
    if (Types.isFunctionTy(tFunc))
        paramTypes = Types.getFuncParamsTypes(tFunc);

    code = instruction::PUSH(); // reservar slot para el valor de retorno

    for (std::size_t i = 0; i < ctx->expr().size(); ++i) {
        auto exprCtx = ctx->expr(i);
        CodeAttribs &&codAt = std::any_cast<CodeAttribs>(visit(exprCtx));
        code = code || codAt.code;

        std::string argAddr = codAt.addr;
        TypesMgr::TypeId tArg = getTypeDecor(exprCtx);
        if (i < paramTypes.size() and Types.isFloatTy(paramTypes[i]) and
            Types.isIntegerTy(tArg)) {
            std::string tmpFloat = "%" + codeCounters.newTEMP();
            code = code || instruction::FLOAT(tmpFloat, argAddr);
            argAddr = tmpFloat;
        }

        code = code || instruction::PUSH(argAddr);
    }

    code = code || instruction::CALL(name);

    for (std::size_t i = 0; i < ctx->expr().size(); ++i) {
        code = code || instruction::POP();
    }

    std::string temp = "%" + codeCounters.newTEMP();
    code = code || instruction::POP(temp);

    CodeAttribs codAts(temp, "", code);
    DEBUG_EXIT();
    return codAts;
}

std::any CodeGenVisitor::visitReadStmt(AslParser::ReadStmtContext *ctx) {
    DEBUG_ENTER();
    CodeAttribs &&codAtsE = std::any_cast<CodeAttribs>(visit(ctx->left_expr()));
    std::string addr1 = codAtsE.addr;
    // std::string          offs1 = codAtsE.offs;
    instructionList &code1 = codAtsE.code;
    instructionList &code = code1;
    // TypesMgr::TypeId tid1 = getTypeDecor(ctx->left_expr());
    code = code1 || instruction::READI(addr1);
    DEBUG_EXIT();
    return code;
}

std::any CodeGenVisitor::visitWriteExpr(AslParser::WriteExprContext *ctx) {
    DEBUG_ENTER();
    CodeAttribs &&codAt1 = std::any_cast<CodeAttribs>(visit(ctx->expr()));
    std::string addr1 = codAt1.addr;
    // std::string         offs1 = codAt1.offs;
    instructionList &code1 = codAt1.code;
    TypesMgr::TypeId tid1 = getTypeDecor(ctx->expr());
    instructionList code2;
    if (Types.isIntegerTy(tid1))
        code2 = instruction::WRITEI(addr1);
    else if (Types.isFloatTy(tid1))
        code2 = instruction::WRITEF(addr1);
    else if (Types.isCharacterTy(tid1))
        code2 = instruction::WRITEC(addr1);
    else if (Types.isBooleanTy(tid1)) {
        code2 = code2 || instruction::WRITEI(addr1);
    }
    instructionList finalCode = code1 || code2;
    DEBUG_EXIT();
    return finalCode;
}

std::any CodeGenVisitor::visitWriteString(AslParser::WriteStringContext *ctx) {
    DEBUG_ENTER();
    instructionList code;
    std::string s = ctx->STRING()->getText();
    code = code || instruction::WRITES(s);
    DEBUG_EXIT();
    return code;
}

// Esto devuelve un puntero
std::any CodeGenVisitor::visitLeft_expr(AslParser::Left_exprContext *ctx) {
    DEBUG_ENTER();
    CodeAttribs &&codAts = std::any_cast<CodeAttribs>(visit(ctx->ident()));

    if (ctx->expr()) {
        CodeAttribs codeAtsExpr =
            std::any_cast<CodeAttribs>(visit(ctx->expr()));

        // Pedir el tamaño del ELEMENTO , no del array
        TypesMgr::TypeId elemType = getTypeDecor(ctx);
        std::size_t elemSize = Types.getSizeOfType(elemType);

        std::string tmpOffset = "%" + codeCounters.newTEMP();
        instructionList code = codAts.code || codeAtsExpr.code;

        code = code || instruction::MUL(tmpOffset, codeAtsExpr.addr,
                                        std::to_string(elemSize));

        // Devuelve la dirección base y el offset por separado
        // codAtsADDR[tmpOffset]
        DEBUG_EXIT();
        return CodeAttribs(codAts.addr, tmpOffset, code);
    }

    DEBUG_EXIT();
    return codAts;
}

std::any
CodeGenVisitor::visitArrayAccessExpr(AslParser::ArrayAccessExprContext *ctx) {
    DEBUG_ENTER();
    CodeAttribs &&arrayAddr = std::any_cast<CodeAttribs>(visit(ctx->ident()));
    CodeAttribs &&indexVal = std::any_cast<CodeAttribs>(visit(ctx->expr()));

    TypesMgr::TypeId elemType = getTypeDecor(ctx);
    std::size_t elemSize = Types.getSizeOfType(elemType);

    std::string tmpOffset = "%" + codeCounters.newTEMP();
    std::string tmpValue = "%" + codeCounters.newTEMP();
    instructionList code = arrayAddr.code || indexVal.code;

    code = code || instruction::MUL(tmpOffset, indexVal.addr,
                                    std::to_string(elemSize));
    code = code || instruction::LOADX(tmpValue, arrayAddr.addr, tmpOffset);

    DEBUG_EXIT();
    return CodeAttribs(tmpValue, "", code);
}

std::any CodeGenVisitor::visitParenthesis(AslParser::ParenthesisContext *ctx) {
    DEBUG_ENTER();
    CodeAttribs &&codAt = std::any_cast<CodeAttribs>(visit(ctx->expr()));
    DEBUG_EXIT();
    return codAt;
}

std::any
CodeGenVisitor::visitUnaryOperator(AslParser::UnaryOperatorContext *ctx) {
    DEBUG_ENTER();
    CodeAttribs &&codAt = std::any_cast<CodeAttribs>(visit(ctx->expr()));
    std::string addr = codAt.addr;
    std::string op = ctx->op->getText();

    std::string temp = "%" + codeCounters.newTEMP();
    instructionList &code = codAt.code;
    if (op == "-") {
        code = code || instruction::NEG(temp, addr);
    } else {
        code = code || instruction::NOT(temp, addr);
    }

    CodeAttribs codAts(temp, "", code);
    DEBUG_EXIT();
    return codAts;
}

std::any CodeGenVisitor::visitArithmetic(AslParser::ArithmeticContext *ctx) {
    DEBUG_ENTER();
    CodeAttribs &&codAt1 = std::any_cast<CodeAttribs>(visit(ctx->expr(0)));
    std::string addr1 = codAt1.addr;
    instructionList &code1 = codAt1.code;
    CodeAttribs &&codAt2 = std::any_cast<CodeAttribs>(visit(ctx->expr(1)));
    std::string addr2 = codAt2.addr;
    instructionList &code2 = codAt2.code;
    instructionList &&code = code1 || code2;

    TypesMgr::TypeId t1 = getTypeDecor(ctx->expr(0));
    TypesMgr::TypeId t2 = getTypeDecor(ctx->expr(1));
    TypesMgr::TypeId t = getTypeDecor(ctx);

    std::string temp = "%" + codeCounters.newTEMP();
    if (Types.isFloatTy(t)) {
        std::string temp1 = "%" + codeCounters.newTEMP();
        std::string temp2 = "%" + codeCounters.newTEMP();

        if (Types.isFloatTy(t1)) {
            temp1 = addr1;
        } else
            code = code || instruction::FLOAT(temp1, addr1);

        if (Types.isFloatTy(t2)) {
            temp2 = addr2;
        } else
            code = code || instruction::FLOAT(temp2, addr2);

        if (ctx->MUL())
            code = code || instruction::FMUL(temp, temp1, temp2);
        else if (ctx->PLUS())
            code = code || instruction::FADD(temp, temp1, temp2);
        else if (ctx->MINUS())
            code = code || instruction::FSUB(temp, temp1, temp2);
        else if (ctx->DIV())
            code = code || instruction::FDIV(temp, temp1, temp2);
    } else {
        if (ctx->MUL())
            code = code || instruction::MUL(temp, addr1, addr2);
        else if (ctx->PLUS())
            code = code || instruction::ADD(temp, addr1, addr2);
        else if (ctx->MINUS())
            code = code || instruction::SUB(temp, addr1, addr2);
        else if (ctx->DIV())
            code = code || instruction::DIV(temp, addr1, addr2);
        else if (ctx->MOD()) {
            // a mod n = a - (n * (a // n))
            std::string temp3 = "%" + codeCounters.newTEMP();
            std::string temp2 = "%" + codeCounters.newTEMP();

            code = code || instruction::DIV(temp3, addr1, addr2);
            code = code || instruction::MUL(temp2, temp3, addr2);
            code = code || instruction::SUB(temp, addr1, temp2);
        }
    }

    CodeAttribs codAts(temp, "", code);
    DEBUG_EXIT();
    return codAts;
}

std::any CodeGenVisitor::visitNot(AslParser::NotContext *ctx) {
    DEBUG_ENTER();
    CodeAttribs codAt = std::any_cast<CodeAttribs>(visit(ctx->expr()));
    std::string temp = "%" + codeCounters.newTEMP();

    instructionList code = codAt.code || instruction::NOT(temp, codAt.addr);

    CodeAttribs codAts(temp, "", code);
    DEBUG_EXIT();
    return codAts;
}

std::any CodeGenVisitor::visitLogicalAnd(AslParser::LogicalAndContext *ctx) {
    DEBUG_ENTER();
    CodeAttribs &&codAtexpr1 = std::any_cast<CodeAttribs>(visit(ctx->expr(0)));
    CodeAttribs &&codAtexpr2 = std::any_cast<CodeAttribs>(visit(ctx->expr(1)));

    instructionList &expr1 = codAtexpr1.code;
    instructionList &expr2 = codAtexpr2.code;

    std::string addr1 = codAtexpr1.addr;
    std::string addr2 = codAtexpr2.addr;

    std::string tmp = "%" + codeCounters.newTEMP();
    instructionList &&code = expr1 || expr2;
    code = code || instruction::AND(tmp, addr1, addr2);

    CodeAttribs codAts(tmp, "", code);
    DEBUG_EXIT();
    return codAts;
}

std::any CodeGenVisitor::visitLogicalOr(AslParser::LogicalOrContext *ctx) {
    DEBUG_ENTER();
    CodeAttribs &&codAtexpr1 = std::any_cast<CodeAttribs>(visit(ctx->expr(0)));
    CodeAttribs &&codAtexpr2 = std::any_cast<CodeAttribs>(visit(ctx->expr(1)));

    instructionList &expr1 = codAtexpr1.code;
    instructionList &expr2 = codAtexpr2.code;

    std::string addr1 = codAtexpr1.addr;
    std::string addr2 = codAtexpr2.addr;

    std::string tmp = "%" + codeCounters.newTEMP();
    instructionList &&code = expr1 || expr2;
    code = code || instruction::OR(tmp, addr1, addr2);

    CodeAttribs codAts(tmp, "", code);
    DEBUG_EXIT();
    return codAts;
}

std::any CodeGenVisitor::visitRelational(AslParser::RelationalContext *ctx) {
    DEBUG_ENTER();
    CodeAttribs &&codAt1 = std::any_cast<CodeAttribs>(visit(ctx->expr(0)));
    std::string addr1 = codAt1.addr;
    instructionList &code1 = codAt1.code;
    CodeAttribs &&codAt2 = std::any_cast<CodeAttribs>(visit(ctx->expr(1)));
    std::string addr2 = codAt2.addr;
    instructionList &code2 = codAt2.code;
    instructionList &&code = code1 || code2;

    TypesMgr::TypeId typeExpr1 = getTypeDecor(ctx->expr(0));
    TypesMgr::TypeId typeExpr2 = getTypeDecor(ctx->expr(1));
    bool useFloatCmp = Types.isNumericTy(typeExpr1) &&
                       Types.isNumericTy(typeExpr2) &&
                       (Types.isFloatTy(typeExpr1) || Types.isFloatTy(typeExpr2));

    std::string leftAddr = addr1;
    std::string rightAddr = addr2;
    if (useFloatCmp) {
        if (Types.isIntegerTy(typeExpr1)) {
            leftAddr = "%" + codeCounters.newTEMP();
            code = code || instruction::FLOAT(leftAddr, addr1);
        }
        if (Types.isIntegerTy(typeExpr2)) {
            rightAddr = "%" + codeCounters.newTEMP();
            code = code || instruction::FLOAT(rightAddr, addr2);
        }
    }

    std::string op = ctx->op->getText();
    std::string temp = "%" + codeCounters.newTEMP();
    std::string temp1 = "%" + codeCounters.newTEMP();
    if (op == "==") {
        if (useFloatCmp)
            code = code || instruction::FEQ(temp, leftAddr, rightAddr);
        else
            code = code || instruction::EQ(temp, leftAddr, rightAddr);
    } else if (op == "<") {
        if (useFloatCmp)
            code = code || instruction::FLT(temp, leftAddr, rightAddr);
        else
            code = code || instruction::LT(temp, leftAddr, rightAddr);
    } else if (op == "<=") {
        if (useFloatCmp)
            code = code || instruction::FLE(temp, leftAddr, rightAddr);
        else
            code = code || instruction::LE(temp, leftAddr, rightAddr);
    } else if (op == "!=") {
        if (useFloatCmp)
            code = code || instruction::FEQ(temp1, leftAddr, rightAddr);
        else
            code = code || instruction::EQ(temp1, leftAddr, rightAddr);
        code = code || instruction::NOT(temp, temp1);
    } else if (op == ">") {
        if (useFloatCmp)
            code = code || instruction::FLE(temp1, leftAddr, rightAddr);
        else
            code = code || instruction::LE(temp1, leftAddr, rightAddr);
        code = code || instruction::NOT(temp, temp1);
    } else {
        if (useFloatCmp)
            code = code || instruction::FLT(temp1, leftAddr, rightAddr);
        else
            code = code || instruction::LT(temp1, leftAddr, rightAddr);
        code = code || instruction::NOT(temp, temp1);
    }

    CodeAttribs codAts(temp, "", code);
    DEBUG_EXIT();
    return codAts;
}

std::any CodeGenVisitor::visitValue(AslParser::ValueContext *ctx) {
    DEBUG_ENTER();
    instructionList code;
    TypesMgr::TypeId type = getTypeDecor(ctx);
    std::string temp = "%" + codeCounters.newTEMP();
    if (Types.isBooleanTy(type)) {
        if (ctx->getText() == "true")
            code = instruction::ILOAD(temp, "1");
        else
            code = instruction::ILOAD(temp, "0");
    } else if (Types.isCharacterTy(type))
        code = instruction::CLOAD(temp, ctx->getText());
    else if (Types.isFloatTy(type))
        code = instruction::FLOAD(temp, ctx->getText());
    else
        code = instruction::ILOAD(temp, ctx->getText());
    CodeAttribs codAts(temp, "", code);
    DEBUG_EXIT();
    return codAts;
}

std::any CodeGenVisitor::visitExprIdent(AslParser::ExprIdentContext *ctx) {
    DEBUG_ENTER();
    CodeAttribs &&codAts = std::any_cast<CodeAttribs>(visit(ctx->ident()));
    DEBUG_EXIT();
    return codAts;
}

std::any CodeGenVisitor::visitIdent(AslParser::IdentContext *ctx) {
    DEBUG_ENTER();
    CodeAttribs codAts(ctx->ID()->getText(), "", instructionList());
    DEBUG_EXIT();
    return codAts;
}

std::any CodeGenVisitor::visitWhileStmt(AslParser::WhileStmtContext *ctx) {
    DEBUG_ENTER();
    CodeAttribs &&codeEval = std::any_cast<CodeAttribs>(visit(ctx->expr()));
    instructionList &&codAts =
        std::any_cast<instructionList>(visit(ctx->statements()));
    std::string temp1 = "L" + codeCounters.newLabelWHILE();
    std::string temp2 = "L" + codeCounters.newLabelWHILE();

    instructionList code;
    code = instruction::LABEL(temp1) || codeEval.code;
    code = code || instruction::FJUMP(codeEval.addr, temp2);
    code = code || codAts;
    code = code || instruction::UJUMP(temp1);
    code = code || instruction::LABEL(temp2);

    DEBUG_EXIT();
    return code;
}

// Getters for the necessary tree node atributes:
//   Scope and Type
SymTable::ScopeId
CodeGenVisitor::getScopeDecor(antlr4::ParserRuleContext *ctx) const {
    return Decorations.getScope(ctx);
}
TypesMgr::TypeId
CodeGenVisitor::getTypeDecor(antlr4::ParserRuleContext *ctx) const {
    return Decorations.getType(ctx);
}

// Constructors of the class CodeAttribs:
//
CodeGenVisitor::CodeAttribs::CodeAttribs(const std::string &addr,
                                         const std::string &offs,
                                         instructionList &code)
    : addr{addr}, offs{offs}, code{code} {}

CodeGenVisitor::CodeAttribs::CodeAttribs(const std::string &addr,
                                         const std::string &offs,
                                         instructionList &&code)
    : addr{addr}, offs{offs}, code{code} {}
