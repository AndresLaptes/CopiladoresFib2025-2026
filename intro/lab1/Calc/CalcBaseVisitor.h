
// Generated from Calc.g4 by ANTLR 4.13.2

#pragma once


#include "antlr4-runtime.h"
#include "CalcVisitor.h"


/**
 * This class provides an empty implementation of CalcVisitor, which can be
 * extended to create a visitor which only needs to handle a subset of the available methods.
 */
class  CalcBaseVisitor : public CalcVisitor {
public:

  virtual std::any visitProg(CalcParser::ProgContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitCondicionalIF(CalcParser::CondicionalIFContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitBucleWhile(CalcParser::BucleWhileContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitPrintExpr(CalcParser::PrintExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAssign(CalcParser::AssignContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitBlank(CalcParser::BlankContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitParentesis(CalcParser::ParentesisContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitNegation(CalcParser::NegationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitProd(CalcParser::ProdContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAbsValue(CalcParser::AbsValueContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitCondicionalCompacto(CalcParser::CondicionalCompactoContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitLogicalOperation(CalcParser::LogicalOperationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitUnaryMinus(CalcParser::UnaryMinusContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitOPBin(CalcParser::OPBinContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFunctionsOperations(CalcParser::FunctionsOperationsContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitId(CalcParser::IdContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitInt(CalcParser::IntContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitPlus(CalcParser::PlusContext *ctx) override {
    return visitChildren(ctx);
  }


};

