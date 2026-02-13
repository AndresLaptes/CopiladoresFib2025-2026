
#include "antlr4-runtime.h"
#include "CalcLexer.h"
#include "CalcParser.h"
#include "CalcBaseVisitor.h"

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <cmath>
#include <cstdio>     // fopen
#include <cstdlib>    // EXIT_FAILURE, EXIT_SUCCESS
#include <limits>

// using namespace std;
// using namespace antlr4;
// using namespace antlrcpp;


//////////////////////////////////////////////////////////////////////
// Sample "calculator" (implemented with a visitor)
class Calculator : public CalcBaseVisitor {
public:
    bool evaluarCondicionales(std::string comparador, int left, int right) {
        static std::map<std::string, int> memoria = {{">", 1}, {"<", 2}, {"==", 3}, {"!=", 4}, {">=", 5}, {"<=", 6}};
        
        switch (memoria[comparador]) {
            case 1: return (bool) (left > right);
            case 2: return (bool) (left < right);
            case 3: return (bool) (left == right);
            case 4: return (bool) (left != right);
            case 5: return (bool) (left >= right);
            case 6: return (bool) (left <= right);
        }

        return false;
    }

  // "memory" for the calculator; variable/value pairs go here
  std::map<std::string, int> memory;

  // stat : expr NEWLINE
  std::any visitPrintExpr(CalcParser::PrintExprContext *ctx) {
    int value = std::any_cast<int>(visit(ctx->expr()));  // evaluate the expr child
    std::cout << value << std::endl;                     // print the result
    return 0;                                            // return dummy value
  }

  // stat : ID '=' expr NEWLINE
  std::any visitAssign(CalcParser::AssignContext *ctx) {
    std::string id = ctx->ID()->getText();               // id is left-hand side of '='
    int value = std::any_cast<int>(visit(ctx->expr()));  // compute value of expression on right
    memory[id] = value;                                  // store it in the memory
    return 0;                                            // return dummy value
  }

  // expr : expr (MUL|DIV) expr
  std::any visitProd(CalcParser::ProdContext *ctx) {
    int left = std::any_cast<int>(visit(ctx->expr(0)));   // get value of left subexpression
    int right = std::any_cast<int>(visit(ctx->expr(1)));  // get value of right subexpression
    if (ctx->MUL()) return left*right;
    else return left/right; 
  }
  
  // expr : expr (ADD|SUB) expr
  std::any visitPlus(CalcParser::PlusContext *ctx) {
    int left = std::any_cast<int>(visit(ctx->expr(0)));   // get value of left subexpression
    int right = std::any_cast<int>(visit(ctx->expr(1)));  // get value of right subexpression
    if (ctx->ADD()) return left+right;
    else return left-right;
  }
  
  // expr : INT
  std::any visitInt(CalcParser::IntContext *ctx) {
    return std::stoi(ctx->INT()->getText());       // or: ctx->getText()
  }
  
  // expr : ID
  std::any visitId(CalcParser::IdContext *ctx) {
    std::string id = ctx->ID()->getText();         // or: ctx->getText()
    if (memory.find(id) != memory.end()) return memory[id];
    return 0;
  }
  
  std::any visitUnaryMinus(CalcParser::UnaryMinusContext *ctx) {
        std::string id = ctx->ID()->getText();
        if (memory.find(id) != memory.end()) {
            int newValor = memory[id] - 1;
            memory[id] = newValor;
            return newValor;
        }

        return 0;
  }

  std::any visitParentesis(CalcParser::ParentesisContext *ctx) {
        return visit(ctx->expr());
  }

  std::any visitOPBin(CalcParser::OPBinContext *ctx) {
        static std::map<std::string, int> memoria = {{">", 1}, {"<", 2}, {"==", 3}, {"!=", 4}, {">=", 5}, {"<=", 6}};

        std::string idOp = ctx->OPBIN()->getText();
        int left = std::any_cast<int>(visit(ctx->expr(0)));
        int right = std::any_cast<int>(visit(ctx->expr(1)));
        
        switch (memoria[idOp]) {
            case 1: return (int) (left > right);
            case 2: return (int) (left < right);
            case 3: return (int) (left == right);
            case 4: return (int) (left != right);
            case 5: return (int) (left >= right);
            case 6: return (int) (left <= right);
        }

        return 0;
  }

  std::any visitNegation(CalcParser::NegationContext *ctx) {
    int valorActual = std::any_cast<int>(visit(ctx->expr()));
    
    if (valorActual == 0) return 1;
    else return 0;
  }

  std::any visitLogicalOperation(CalcParser::LogicalOperationContext *ctx) {
        std::string operador = ctx->LOGIC()->getText();

        int left = std::any_cast<int>(visit(ctx->expr(0)));
        int right = std::any_cast<int>(visit(ctx->expr(1)));
        
        if (operador == "and") return (int) (left && right);
        return (int) (left || right);
  }


  std::any visitFunctionsOperations(CalcParser::FunctionsOperationsContext *ctx) {
    std::string funcion = ctx->FUN()->getText();

    int numVar = ctx->expr().size();

    if (numVar > 1) {
        if (funcion == "pow") {
            int first = std::any_cast<int>(visit(ctx->expr(0)));
            
            if (numVar == 2) {
                int second = std::any_cast<int>(visit(ctx->expr(1)));

                return (int) (pow(first, second));
            } else return first;

        } 

        if (funcion == "max") {
            int actualMax = 0;
            for (auto act : ctx->expr()) {
                int actualElement = std::any_cast<int>(visit(act));

                if (actualElement > actualMax) actualMax = actualElement;
            } 

            return actualMax;
        }

        if (funcion == "min") {
            int actualMin = std::numeric_limits<int>::max();
            for (auto act : ctx->expr()) {
                int actualElement = std::any_cast<int>(visit(act));

                if (actualElement < actualMin) actualMin = actualElement;
            } 

            return actualMin;
        }

        if (funcion == "sum") {
            int actualSum = 0;
            for (auto act : ctx->expr()) {
                int actualElement = std::any_cast<int>(visit(act));

                actualSum += actualElement;
            } 

            return actualSum;
        }
    }

    return (int) (std::any_cast<int>(visit(ctx->expr(0))));
  }

  std::any visitAbsValue(CalcParser::AbsValueContext *ctx) {
    int value = std::any_cast<int>(visit(ctx->expr()));
    
    if (value < 0) return value * -1;
    return value;
   }

    std::any visitCondicionalCompacto(CalcParser::CondicionalCompactoContext *ctx) {
        std::string operacionCondicion = ctx->OPBIN()->getText();

        int left = std::any_cast<int>(visit(ctx->expr(0)));
        int right = std::any_cast<int>(visit(ctx->expr(1)));
        
        bool condicion = evaluarCondicionales(operacionCondicion, left, right);

        if (condicion) return visit(ctx->expr(2));
        
        return visit(ctx->expr(3));
    }

    std::any visitCondicionalIF(CalcParser::CondicionalIFContext *ctx) {
        std::string operacionCondicion = ctx->OPBIN()->getText();
        
        int left = std::any_cast<int>(visit(ctx->expr(0)));
        int right = std::any_cast<int>(visit(ctx->expr(1)));

        bool condicion = evaluarCondicionales(operacionCondicion, left, right);

        if (condicion) {
            for(auto act : ctx->thenStat) {
                visit(act);
            }
        } else {
            for (auto act : ctx->elseStat) {
                visit(act);
            }
        }

        return 0;
    }


    std::any visitBucleWhile(CalcParser::BucleWhileContext *ctx) {
        std::string operacionCondicion = ctx->OPBIN()->getText();
        
        int left = std::any_cast<int>(visit(ctx->expr(0)));
        int right = std::any_cast<int>(visit(ctx->expr(1)));

        bool condicion = evaluarCondicionales(operacionCondicion, left, right);

        while (condicion) {
            for (auto act : ctx->stat()) visit(act);
            left = std::any_cast<int>(visit(ctx->expr(0)));
            right = std::any_cast<int>(visit(ctx->expr(1)));
           
            condicion = evaluarCondicionales(operacionCondicion, left, right);
        }
        
        return 0;
    }
};
// Sample "calculator" (implemented with a visitor)
//////////////////////////////////////////////////////////////////////


int main(int argc, const char* argv[]) {
  // check the correct use of the program
  if (argc > 2) {
    std::cout << "Usage: ./main [<file>]" << std::endl;
    return EXIT_FAILURE;
  }
  if (argc == 2 and not std::fopen(argv[1], "r")) {
    std::cout << "No such file: " << argv[1] << std::endl;
    return EXIT_FAILURE;
  }

  // open input file (or std::cin) and create a character stream
  antlr4::ANTLRInputStream input;
  if (argc == 2) {  // reads from <file>
    std::ifstream stream;
    stream.open(argv[1]);
    input = antlr4::ANTLRInputStream(stream);
  }
  else {            // reads fron std::cin
    input = antlr4::ANTLRInputStream(std::cin);
  }

  // create a lexer that consumes the character stream and produce a token stream
  CalcLexer lexer(&input);
  antlr4::CommonTokenStream tokens(&lexer);

  // create a parser that consumes the token stream, and parses it.
  CalcParser parser(&tokens);

  // call the parser and get the parse tree. prog is the initial rule
  antlr4::tree::ParseTree *tree = parser.prog();

  // check for lexical or syntactical errors
  if (lexer.getNumberOfSyntaxErrors() > 0 or
      parser.getNumberOfSyntaxErrors() > 0) {
    std::cout << "Lexical and/or syntactical errors have been found." << std::endl;
    return EXIT_FAILURE;
  }
  
  // print the parse tree (for debugging purposes)
  std::cout << tree->toStringTree(&parser) << std::endl;

  ////////////////////////////////////////////////////////////////////

  // Create a visitor that will execute the statements
  Calculator calc;

  // Traverse the tree using this Calculator visitor
  calc.visit(tree);

  return EXIT_SUCCESS;
}
