
// Generated from Calc.g4 by ANTLR 4.13.2

#pragma once


#include "antlr4-runtime.h"
#include "CalcParser.h"



/**
 * This class defines an abstract visitor for a parse tree
 * produced by CalcParser.
 */
class  CalcVisitor : public antlr4::tree::AbstractParseTreeVisitor {
public:

  /**
   * Visit parse trees produced by CalcParser.
   */
    virtual std::any visitProg(CalcParser::ProgContext *context) = 0;

    virtual std::any visitCondicionalIF(CalcParser::CondicionalIFContext *context) = 0;

    virtual std::any visitBucleWhile(CalcParser::BucleWhileContext *context) = 0;

    virtual std::any visitPrintExpr(CalcParser::PrintExprContext *context) = 0;

    virtual std::any visitAssign(CalcParser::AssignContext *context) = 0;

    virtual std::any visitBlank(CalcParser::BlankContext *context) = 0;

    virtual std::any visitParentesis(CalcParser::ParentesisContext *context) = 0;

    virtual std::any visitNegation(CalcParser::NegationContext *context) = 0;

    virtual std::any visitProd(CalcParser::ProdContext *context) = 0;

    virtual std::any visitAbsValue(CalcParser::AbsValueContext *context) = 0;

    virtual std::any visitCondicionalCompacto(CalcParser::CondicionalCompactoContext *context) = 0;

    virtual std::any visitLogicalOperation(CalcParser::LogicalOperationContext *context) = 0;

    virtual std::any visitUnaryMinus(CalcParser::UnaryMinusContext *context) = 0;

    virtual std::any visitOPBin(CalcParser::OPBinContext *context) = 0;

    virtual std::any visitFunctionsOperations(CalcParser::FunctionsOperationsContext *context) = 0;

    virtual std::any visitId(CalcParser::IdContext *context) = 0;

    virtual std::any visitInt(CalcParser::IntContext *context) = 0;

    virtual std::any visitPlus(CalcParser::PlusContext *context) = 0;


};

