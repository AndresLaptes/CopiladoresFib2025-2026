
// Generated from Asl.g4 by ANTLR 4.13.2

#pragma once


#include "antlr4-runtime.h"




class  AslLexer : public antlr4::Lexer {
public:
  enum {
    T__0 = 1, T__1 = 2, T__2 = 3, T__3 = 4, T__4 = 5, AND = 6, OR = 7, NOT = 8, 
    LT = 9, GT = 10, NEQ = 11, LEQ = 12, GEQ = 13, ASSIGN = 14, EQUAL = 15, 
    PLUS = 16, MINUS = 17, MUL = 18, DIV = 19, VAR = 20, INT = 21, BOOL = 22, 
    FLOAT = 23, CHAR = 24, IF = 25, THEN = 26, ELSE = 27, ENDIF = 28, FUNC = 29, 
    ENDFUNC = 30, READ = 31, WRITE = 32, BOOLVAL = 33, ID = 34, INTVAL = 35, 
    FLOATVAL = 36, STRING = 37, CHARVAL = 38, COMMENT = 39, WS = 40
  };

  explicit AslLexer(antlr4::CharStream *input);

  ~AslLexer() override;


  std::string getGrammarFileName() const override;

  const std::vector<std::string>& getRuleNames() const override;

  const std::vector<std::string>& getChannelNames() const override;

  const std::vector<std::string>& getModeNames() const override;

  const antlr4::dfa::Vocabulary& getVocabulary() const override;

  antlr4::atn::SerializedATNView getSerializedATN() const override;

  const antlr4::atn::ATN& getATN() const override;

  // By default the static state used to implement the lexer is lazily initialized during the first
  // call to the constructor. You can call this function if you wish to initialize the static state
  // ahead of time.
  static void initialize();

private:

  // Individual action functions triggered by action() above.

  // Individual semantic predicate functions triggered by sempred() above.

};

