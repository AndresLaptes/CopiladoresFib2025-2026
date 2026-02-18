
// Generated from Calc.g4 by ANTLR 4.13.2


#include "CalcVisitor.h"

#include "CalcParser.h"


using namespace antlrcpp;

using namespace antlr4;

namespace {

struct CalcParserStaticData final {
  CalcParserStaticData(std::vector<std::string> ruleNames,
                        std::vector<std::string> literalNames,
                        std::vector<std::string> symbolicNames)
      : ruleNames(std::move(ruleNames)), literalNames(std::move(literalNames)),
        symbolicNames(std::move(symbolicNames)),
        vocabulary(this->literalNames, this->symbolicNames) {}

  CalcParserStaticData(const CalcParserStaticData&) = delete;
  CalcParserStaticData(CalcParserStaticData&&) = delete;
  CalcParserStaticData& operator=(const CalcParserStaticData&) = delete;
  CalcParserStaticData& operator=(CalcParserStaticData&&) = delete;

  std::vector<antlr4::dfa::DFA> decisionToDFA;
  antlr4::atn::PredictionContextCache sharedContextCache;
  const std::vector<std::string> ruleNames;
  const std::vector<std::string> literalNames;
  const std::vector<std::string> symbolicNames;
  const antlr4::dfa::Vocabulary vocabulary;
  antlr4::atn::SerializedATNView serializedATN;
  std::unique_ptr<antlr4::atn::ATN> atn;
};

::antlr4::internal::OnceFlag calcParserOnceFlag;
#if ANTLR4_USE_THREAD_LOCAL_CACHE
static thread_local
#endif
std::unique_ptr<CalcParserStaticData> calcParserStaticData = nullptr;

void calcParserInitialize() {
#if ANTLR4_USE_THREAD_LOCAL_CACHE
  if (calcParserStaticData != nullptr) {
    return;
  }
#else
  assert(calcParserStaticData == nullptr);
#endif
  auto staticData = std::make_unique<CalcParserStaticData>(
    std::vector<std::string>{
      "prog", "stat", "expr"
    },
    std::vector<std::string>{
      "", "'IF'", "'ENDIF'", "'ELSE'", "'ENDELSE'", "'WHILE'", "'ENDWHILE'", 
      "'='", "'('", "')'", "','", "'['", "'\\u003F'", "':'", "']'", "'abs'", 
      "", "'*'", "'/'", "'+'", "'-'", "'not'"
    },
    std::vector<std::string>{
      "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "ABS", 
      "FUN", "MUL", "DIV", "ADD", "SUB", "NOT", "LOGIC", "OPBIN", "ID", 
      "INT", "NEWLINE", "WS"
    }
  );
  static const int32_t serializedATNSegment[] = {
  	4,1,27,119,2,0,7,0,2,1,7,1,2,2,7,2,1,0,4,0,8,8,0,11,0,12,0,9,1,0,1,0,
  	1,1,1,1,1,1,1,1,1,1,1,1,5,1,20,8,1,10,1,12,1,23,9,1,1,1,1,1,1,1,1,1,5,
  	1,29,8,1,10,1,12,1,32,9,1,1,1,1,1,3,1,36,8,1,1,1,1,1,1,1,1,1,1,1,1,1,
  	5,1,44,8,1,10,1,12,1,47,9,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
  	1,3,1,60,8,1,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,
  	1,2,1,2,1,2,5,2,79,8,2,10,2,12,2,82,9,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,
  	2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,3,2,100,8,2,1,2,1,2,1,2,1,2,1,2,1,2,
  	1,2,1,2,1,2,1,2,1,2,1,2,5,2,114,8,2,10,2,12,2,117,9,2,1,2,0,1,4,3,0,2,
  	4,0,2,1,0,17,18,1,0,19,20,136,0,7,1,0,0,0,2,59,1,0,0,0,4,99,1,0,0,0,6,
  	8,3,2,1,0,7,6,1,0,0,0,8,9,1,0,0,0,9,7,1,0,0,0,9,10,1,0,0,0,10,11,1,0,
  	0,0,11,12,5,0,0,1,12,1,1,0,0,0,13,14,5,1,0,0,14,15,3,4,2,0,15,16,5,23,
  	0,0,16,17,3,4,2,0,17,21,5,26,0,0,18,20,3,2,1,0,19,18,1,0,0,0,20,23,1,
  	0,0,0,21,19,1,0,0,0,21,22,1,0,0,0,22,24,1,0,0,0,23,21,1,0,0,0,24,25,5,
  	2,0,0,25,35,5,26,0,0,26,30,5,3,0,0,27,29,3,2,1,0,28,27,1,0,0,0,29,32,
  	1,0,0,0,30,28,1,0,0,0,30,31,1,0,0,0,31,33,1,0,0,0,32,30,1,0,0,0,33,34,
  	5,4,0,0,34,36,5,26,0,0,35,26,1,0,0,0,35,36,1,0,0,0,36,60,1,0,0,0,37,38,
  	5,5,0,0,38,39,3,4,2,0,39,40,5,23,0,0,40,41,3,4,2,0,41,45,5,26,0,0,42,
  	44,3,2,1,0,43,42,1,0,0,0,44,47,1,0,0,0,45,43,1,0,0,0,45,46,1,0,0,0,46,
  	48,1,0,0,0,47,45,1,0,0,0,48,49,5,6,0,0,49,60,1,0,0,0,50,51,3,4,2,0,51,
  	52,5,26,0,0,52,60,1,0,0,0,53,54,5,24,0,0,54,55,5,7,0,0,55,56,3,4,2,0,
  	56,57,5,26,0,0,57,60,1,0,0,0,58,60,5,26,0,0,59,13,1,0,0,0,59,37,1,0,0,
  	0,59,50,1,0,0,0,59,53,1,0,0,0,59,58,1,0,0,0,60,3,1,0,0,0,61,62,6,2,-1,
  	0,62,63,5,21,0,0,63,100,3,4,2,12,64,65,5,8,0,0,65,66,3,4,2,0,66,67,5,
  	9,0,0,67,100,1,0,0,0,68,69,5,15,0,0,69,70,5,8,0,0,70,71,3,4,2,0,71,72,
  	5,9,0,0,72,100,1,0,0,0,73,74,5,16,0,0,74,75,5,8,0,0,75,80,3,4,2,0,76,
  	77,5,10,0,0,77,79,3,4,2,0,78,76,1,0,0,0,79,82,1,0,0,0,80,78,1,0,0,0,80,
  	81,1,0,0,0,81,83,1,0,0,0,82,80,1,0,0,0,83,84,5,9,0,0,84,100,1,0,0,0,85,
  	86,5,11,0,0,86,87,3,4,2,0,87,88,5,23,0,0,88,89,3,4,2,0,89,90,5,12,0,0,
  	90,91,3,4,2,0,91,92,5,13,0,0,92,93,3,4,2,0,93,94,5,14,0,0,94,100,1,0,
  	0,0,95,96,5,20,0,0,96,100,5,24,0,0,97,100,5,25,0,0,98,100,5,24,0,0,99,
  	61,1,0,0,0,99,64,1,0,0,0,99,68,1,0,0,0,99,73,1,0,0,0,99,85,1,0,0,0,99,
  	95,1,0,0,0,99,97,1,0,0,0,99,98,1,0,0,0,100,115,1,0,0,0,101,102,10,10,
  	0,0,102,103,7,0,0,0,103,114,3,4,2,11,104,105,10,9,0,0,105,106,7,1,0,0,
  	106,114,3,4,2,10,107,108,10,8,0,0,108,109,5,23,0,0,109,114,3,4,2,9,110,
  	111,10,7,0,0,111,112,5,22,0,0,112,114,3,4,2,8,113,101,1,0,0,0,113,104,
  	1,0,0,0,113,107,1,0,0,0,113,110,1,0,0,0,114,117,1,0,0,0,115,113,1,0,0,
  	0,115,116,1,0,0,0,116,5,1,0,0,0,117,115,1,0,0,0,10,9,21,30,35,45,59,80,
  	99,113,115
  };
  staticData->serializedATN = antlr4::atn::SerializedATNView(serializedATNSegment, sizeof(serializedATNSegment) / sizeof(serializedATNSegment[0]));

  antlr4::atn::ATNDeserializer deserializer;
  staticData->atn = deserializer.deserialize(staticData->serializedATN);

  const size_t count = staticData->atn->getNumberOfDecisions();
  staticData->decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    staticData->decisionToDFA.emplace_back(staticData->atn->getDecisionState(i), i);
  }
  calcParserStaticData = std::move(staticData);
}

}

CalcParser::CalcParser(TokenStream *input) : CalcParser(input, antlr4::atn::ParserATNSimulatorOptions()) {}

CalcParser::CalcParser(TokenStream *input, const antlr4::atn::ParserATNSimulatorOptions &options) : Parser(input) {
  CalcParser::initialize();
  _interpreter = new atn::ParserATNSimulator(this, *calcParserStaticData->atn, calcParserStaticData->decisionToDFA, calcParserStaticData->sharedContextCache, options);
}

CalcParser::~CalcParser() {
  delete _interpreter;
}

const atn::ATN& CalcParser::getATN() const {
  return *calcParserStaticData->atn;
}

std::string CalcParser::getGrammarFileName() const {
  return "Calc.g4";
}

const std::vector<std::string>& CalcParser::getRuleNames() const {
  return calcParserStaticData->ruleNames;
}

const dfa::Vocabulary& CalcParser::getVocabulary() const {
  return calcParserStaticData->vocabulary;
}

antlr4::atn::SerializedATNView CalcParser::getSerializedATN() const {
  return calcParserStaticData->serializedATN;
}


//----------------- ProgContext ------------------------------------------------------------------

CalcParser::ProgContext::ProgContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CalcParser::ProgContext::EOF() {
  return getToken(CalcParser::EOF, 0);
}

std::vector<CalcParser::StatContext *> CalcParser::ProgContext::stat() {
  return getRuleContexts<CalcParser::StatContext>();
}

CalcParser::StatContext* CalcParser::ProgContext::stat(size_t i) {
  return getRuleContext<CalcParser::StatContext>(i);
}


size_t CalcParser::ProgContext::getRuleIndex() const {
  return CalcParser::RuleProg;
}


std::any CalcParser::ProgContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CalcVisitor*>(visitor))
    return parserVisitor->visitProg(this);
  else
    return visitor->visitChildren(this);
}

CalcParser::ProgContext* CalcParser::prog() {
  ProgContext *_localctx = _tracker.createInstance<ProgContext>(_ctx, getState());
  enterRule(_localctx, 0, CalcParser::RuleProg);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(7); 
    _errHandler->sync(this);
    _la = _input->LA(1);
    do {
      setState(6);
      stat();
      setState(9); 
      _errHandler->sync(this);
      _la = _input->LA(1);
    } while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 120686882) != 0));
    setState(11);
    match(CalcParser::EOF);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- StatContext ------------------------------------------------------------------

CalcParser::StatContext::StatContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t CalcParser::StatContext::getRuleIndex() const {
  return CalcParser::RuleStat;
}

void CalcParser::StatContext::copyFrom(StatContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- BlankContext ------------------------------------------------------------------

tree::TerminalNode* CalcParser::BlankContext::NEWLINE() {
  return getToken(CalcParser::NEWLINE, 0);
}

CalcParser::BlankContext::BlankContext(StatContext *ctx) { copyFrom(ctx); }


std::any CalcParser::BlankContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CalcVisitor*>(visitor))
    return parserVisitor->visitBlank(this);
  else
    return visitor->visitChildren(this);
}
//----------------- CondicionalIFContext ------------------------------------------------------------------

std::vector<CalcParser::ExprContext *> CalcParser::CondicionalIFContext::expr() {
  return getRuleContexts<CalcParser::ExprContext>();
}

CalcParser::ExprContext* CalcParser::CondicionalIFContext::expr(size_t i) {
  return getRuleContext<CalcParser::ExprContext>(i);
}

tree::TerminalNode* CalcParser::CondicionalIFContext::OPBIN() {
  return getToken(CalcParser::OPBIN, 0);
}

std::vector<tree::TerminalNode *> CalcParser::CondicionalIFContext::NEWLINE() {
  return getTokens(CalcParser::NEWLINE);
}

tree::TerminalNode* CalcParser::CondicionalIFContext::NEWLINE(size_t i) {
  return getToken(CalcParser::NEWLINE, i);
}

std::vector<CalcParser::StatContext *> CalcParser::CondicionalIFContext::stat() {
  return getRuleContexts<CalcParser::StatContext>();
}

CalcParser::StatContext* CalcParser::CondicionalIFContext::stat(size_t i) {
  return getRuleContext<CalcParser::StatContext>(i);
}

CalcParser::CondicionalIFContext::CondicionalIFContext(StatContext *ctx) { copyFrom(ctx); }


std::any CalcParser::CondicionalIFContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CalcVisitor*>(visitor))
    return parserVisitor->visitCondicionalIF(this);
  else
    return visitor->visitChildren(this);
}
//----------------- BucleWhileContext ------------------------------------------------------------------

std::vector<CalcParser::ExprContext *> CalcParser::BucleWhileContext::expr() {
  return getRuleContexts<CalcParser::ExprContext>();
}

CalcParser::ExprContext* CalcParser::BucleWhileContext::expr(size_t i) {
  return getRuleContext<CalcParser::ExprContext>(i);
}

tree::TerminalNode* CalcParser::BucleWhileContext::OPBIN() {
  return getToken(CalcParser::OPBIN, 0);
}

tree::TerminalNode* CalcParser::BucleWhileContext::NEWLINE() {
  return getToken(CalcParser::NEWLINE, 0);
}

std::vector<CalcParser::StatContext *> CalcParser::BucleWhileContext::stat() {
  return getRuleContexts<CalcParser::StatContext>();
}

CalcParser::StatContext* CalcParser::BucleWhileContext::stat(size_t i) {
  return getRuleContext<CalcParser::StatContext>(i);
}

CalcParser::BucleWhileContext::BucleWhileContext(StatContext *ctx) { copyFrom(ctx); }


std::any CalcParser::BucleWhileContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CalcVisitor*>(visitor))
    return parserVisitor->visitBucleWhile(this);
  else
    return visitor->visitChildren(this);
}
//----------------- PrintExprContext ------------------------------------------------------------------

CalcParser::ExprContext* CalcParser::PrintExprContext::expr() {
  return getRuleContext<CalcParser::ExprContext>(0);
}

tree::TerminalNode* CalcParser::PrintExprContext::NEWLINE() {
  return getToken(CalcParser::NEWLINE, 0);
}

CalcParser::PrintExprContext::PrintExprContext(StatContext *ctx) { copyFrom(ctx); }


std::any CalcParser::PrintExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CalcVisitor*>(visitor))
    return parserVisitor->visitPrintExpr(this);
  else
    return visitor->visitChildren(this);
}
//----------------- AssignContext ------------------------------------------------------------------

tree::TerminalNode* CalcParser::AssignContext::ID() {
  return getToken(CalcParser::ID, 0);
}

CalcParser::ExprContext* CalcParser::AssignContext::expr() {
  return getRuleContext<CalcParser::ExprContext>(0);
}

tree::TerminalNode* CalcParser::AssignContext::NEWLINE() {
  return getToken(CalcParser::NEWLINE, 0);
}

CalcParser::AssignContext::AssignContext(StatContext *ctx) { copyFrom(ctx); }


std::any CalcParser::AssignContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CalcVisitor*>(visitor))
    return parserVisitor->visitAssign(this);
  else
    return visitor->visitChildren(this);
}
CalcParser::StatContext* CalcParser::stat() {
  StatContext *_localctx = _tracker.createInstance<StatContext>(_ctx, getState());
  enterRule(_localctx, 2, CalcParser::RuleStat);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(59);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 5, _ctx)) {
    case 1: {
      _localctx = _tracker.createInstance<CalcParser::CondicionalIFContext>(_localctx);
      enterOuterAlt(_localctx, 1);
      setState(13);
      match(CalcParser::T__0);
      setState(14);
      expr(0);
      setState(15);
      match(CalcParser::OPBIN);
      setState(16);
      expr(0);
      setState(17);
      match(CalcParser::NEWLINE);
      setState(21);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & 120686882) != 0)) {
        setState(18);
        antlrcpp::downCast<CondicionalIFContext *>(_localctx)->statContext = stat();
        antlrcpp::downCast<CondicionalIFContext *>(_localctx)->thenStat.push_back(antlrcpp::downCast<CondicionalIFContext *>(_localctx)->statContext);
        setState(23);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
      setState(24);
      match(CalcParser::T__1);
      setState(25);
      match(CalcParser::NEWLINE);
      setState(35);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == CalcParser::T__2) {
        setState(26);
        match(CalcParser::T__2);
        setState(30);
        _errHandler->sync(this);
        _la = _input->LA(1);
        while ((((_la & ~ 0x3fULL) == 0) &&
          ((1ULL << _la) & 120686882) != 0)) {
          setState(27);
          antlrcpp::downCast<CondicionalIFContext *>(_localctx)->statContext = stat();
          antlrcpp::downCast<CondicionalIFContext *>(_localctx)->elseStat.push_back(antlrcpp::downCast<CondicionalIFContext *>(_localctx)->statContext);
          setState(32);
          _errHandler->sync(this);
          _la = _input->LA(1);
        }
        setState(33);
        match(CalcParser::T__3);
        setState(34);
        match(CalcParser::NEWLINE);
      }
      break;
    }

    case 2: {
      _localctx = _tracker.createInstance<CalcParser::BucleWhileContext>(_localctx);
      enterOuterAlt(_localctx, 2);
      setState(37);
      match(CalcParser::T__4);
      setState(38);
      expr(0);
      setState(39);
      match(CalcParser::OPBIN);
      setState(40);
      expr(0);
      setState(41);
      match(CalcParser::NEWLINE);
      setState(45);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & 120686882) != 0)) {
        setState(42);
        stat();
        setState(47);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
      setState(48);
      match(CalcParser::T__5);
      break;
    }

    case 3: {
      _localctx = _tracker.createInstance<CalcParser::PrintExprContext>(_localctx);
      enterOuterAlt(_localctx, 3);
      setState(50);
      expr(0);
      setState(51);
      match(CalcParser::NEWLINE);
      break;
    }

    case 4: {
      _localctx = _tracker.createInstance<CalcParser::AssignContext>(_localctx);
      enterOuterAlt(_localctx, 4);
      setState(53);
      match(CalcParser::ID);
      setState(54);
      match(CalcParser::T__6);
      setState(55);
      expr(0);
      setState(56);
      match(CalcParser::NEWLINE);
      break;
    }

    case 5: {
      _localctx = _tracker.createInstance<CalcParser::BlankContext>(_localctx);
      enterOuterAlt(_localctx, 5);
      setState(58);
      match(CalcParser::NEWLINE);
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ExprContext ------------------------------------------------------------------

CalcParser::ExprContext::ExprContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t CalcParser::ExprContext::getRuleIndex() const {
  return CalcParser::RuleExpr;
}

void CalcParser::ExprContext::copyFrom(ExprContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- ParentesisContext ------------------------------------------------------------------

CalcParser::ExprContext* CalcParser::ParentesisContext::expr() {
  return getRuleContext<CalcParser::ExprContext>(0);
}

CalcParser::ParentesisContext::ParentesisContext(ExprContext *ctx) { copyFrom(ctx); }


std::any CalcParser::ParentesisContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CalcVisitor*>(visitor))
    return parserVisitor->visitParentesis(this);
  else
    return visitor->visitChildren(this);
}
//----------------- NegationContext ------------------------------------------------------------------

tree::TerminalNode* CalcParser::NegationContext::NOT() {
  return getToken(CalcParser::NOT, 0);
}

CalcParser::ExprContext* CalcParser::NegationContext::expr() {
  return getRuleContext<CalcParser::ExprContext>(0);
}

CalcParser::NegationContext::NegationContext(ExprContext *ctx) { copyFrom(ctx); }


std::any CalcParser::NegationContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CalcVisitor*>(visitor))
    return parserVisitor->visitNegation(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ProdContext ------------------------------------------------------------------

std::vector<CalcParser::ExprContext *> CalcParser::ProdContext::expr() {
  return getRuleContexts<CalcParser::ExprContext>();
}

CalcParser::ExprContext* CalcParser::ProdContext::expr(size_t i) {
  return getRuleContext<CalcParser::ExprContext>(i);
}

tree::TerminalNode* CalcParser::ProdContext::MUL() {
  return getToken(CalcParser::MUL, 0);
}

tree::TerminalNode* CalcParser::ProdContext::DIV() {
  return getToken(CalcParser::DIV, 0);
}

CalcParser::ProdContext::ProdContext(ExprContext *ctx) { copyFrom(ctx); }


std::any CalcParser::ProdContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CalcVisitor*>(visitor))
    return parserVisitor->visitProd(this);
  else
    return visitor->visitChildren(this);
}
//----------------- AbsValueContext ------------------------------------------------------------------

tree::TerminalNode* CalcParser::AbsValueContext::ABS() {
  return getToken(CalcParser::ABS, 0);
}

CalcParser::ExprContext* CalcParser::AbsValueContext::expr() {
  return getRuleContext<CalcParser::ExprContext>(0);
}

CalcParser::AbsValueContext::AbsValueContext(ExprContext *ctx) { copyFrom(ctx); }


std::any CalcParser::AbsValueContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CalcVisitor*>(visitor))
    return parserVisitor->visitAbsValue(this);
  else
    return visitor->visitChildren(this);
}
//----------------- CondicionalCompactoContext ------------------------------------------------------------------

std::vector<CalcParser::ExprContext *> CalcParser::CondicionalCompactoContext::expr() {
  return getRuleContexts<CalcParser::ExprContext>();
}

CalcParser::ExprContext* CalcParser::CondicionalCompactoContext::expr(size_t i) {
  return getRuleContext<CalcParser::ExprContext>(i);
}

tree::TerminalNode* CalcParser::CondicionalCompactoContext::OPBIN() {
  return getToken(CalcParser::OPBIN, 0);
}

CalcParser::CondicionalCompactoContext::CondicionalCompactoContext(ExprContext *ctx) { copyFrom(ctx); }


std::any CalcParser::CondicionalCompactoContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CalcVisitor*>(visitor))
    return parserVisitor->visitCondicionalCompacto(this);
  else
    return visitor->visitChildren(this);
}
//----------------- LogicalOperationContext ------------------------------------------------------------------

std::vector<CalcParser::ExprContext *> CalcParser::LogicalOperationContext::expr() {
  return getRuleContexts<CalcParser::ExprContext>();
}

CalcParser::ExprContext* CalcParser::LogicalOperationContext::expr(size_t i) {
  return getRuleContext<CalcParser::ExprContext>(i);
}

tree::TerminalNode* CalcParser::LogicalOperationContext::LOGIC() {
  return getToken(CalcParser::LOGIC, 0);
}

CalcParser::LogicalOperationContext::LogicalOperationContext(ExprContext *ctx) { copyFrom(ctx); }


std::any CalcParser::LogicalOperationContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CalcVisitor*>(visitor))
    return parserVisitor->visitLogicalOperation(this);
  else
    return visitor->visitChildren(this);
}
//----------------- UnaryMinusContext ------------------------------------------------------------------

tree::TerminalNode* CalcParser::UnaryMinusContext::SUB() {
  return getToken(CalcParser::SUB, 0);
}

tree::TerminalNode* CalcParser::UnaryMinusContext::ID() {
  return getToken(CalcParser::ID, 0);
}

CalcParser::UnaryMinusContext::UnaryMinusContext(ExprContext *ctx) { copyFrom(ctx); }


std::any CalcParser::UnaryMinusContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CalcVisitor*>(visitor))
    return parserVisitor->visitUnaryMinus(this);
  else
    return visitor->visitChildren(this);
}
//----------------- OPBinContext ------------------------------------------------------------------

std::vector<CalcParser::ExprContext *> CalcParser::OPBinContext::expr() {
  return getRuleContexts<CalcParser::ExprContext>();
}

CalcParser::ExprContext* CalcParser::OPBinContext::expr(size_t i) {
  return getRuleContext<CalcParser::ExprContext>(i);
}

tree::TerminalNode* CalcParser::OPBinContext::OPBIN() {
  return getToken(CalcParser::OPBIN, 0);
}

CalcParser::OPBinContext::OPBinContext(ExprContext *ctx) { copyFrom(ctx); }


std::any CalcParser::OPBinContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CalcVisitor*>(visitor))
    return parserVisitor->visitOPBin(this);
  else
    return visitor->visitChildren(this);
}
//----------------- FunctionsOperationsContext ------------------------------------------------------------------

tree::TerminalNode* CalcParser::FunctionsOperationsContext::FUN() {
  return getToken(CalcParser::FUN, 0);
}

std::vector<CalcParser::ExprContext *> CalcParser::FunctionsOperationsContext::expr() {
  return getRuleContexts<CalcParser::ExprContext>();
}

CalcParser::ExprContext* CalcParser::FunctionsOperationsContext::expr(size_t i) {
  return getRuleContext<CalcParser::ExprContext>(i);
}

CalcParser::FunctionsOperationsContext::FunctionsOperationsContext(ExprContext *ctx) { copyFrom(ctx); }


std::any CalcParser::FunctionsOperationsContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CalcVisitor*>(visitor))
    return parserVisitor->visitFunctionsOperations(this);
  else
    return visitor->visitChildren(this);
}
//----------------- IdContext ------------------------------------------------------------------

tree::TerminalNode* CalcParser::IdContext::ID() {
  return getToken(CalcParser::ID, 0);
}

CalcParser::IdContext::IdContext(ExprContext *ctx) { copyFrom(ctx); }


std::any CalcParser::IdContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CalcVisitor*>(visitor))
    return parserVisitor->visitId(this);
  else
    return visitor->visitChildren(this);
}
//----------------- IntContext ------------------------------------------------------------------

tree::TerminalNode* CalcParser::IntContext::INT() {
  return getToken(CalcParser::INT, 0);
}

CalcParser::IntContext::IntContext(ExprContext *ctx) { copyFrom(ctx); }


std::any CalcParser::IntContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CalcVisitor*>(visitor))
    return parserVisitor->visitInt(this);
  else
    return visitor->visitChildren(this);
}
//----------------- PlusContext ------------------------------------------------------------------

std::vector<CalcParser::ExprContext *> CalcParser::PlusContext::expr() {
  return getRuleContexts<CalcParser::ExprContext>();
}

CalcParser::ExprContext* CalcParser::PlusContext::expr(size_t i) {
  return getRuleContext<CalcParser::ExprContext>(i);
}

tree::TerminalNode* CalcParser::PlusContext::ADD() {
  return getToken(CalcParser::ADD, 0);
}

tree::TerminalNode* CalcParser::PlusContext::SUB() {
  return getToken(CalcParser::SUB, 0);
}

CalcParser::PlusContext::PlusContext(ExprContext *ctx) { copyFrom(ctx); }


std::any CalcParser::PlusContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CalcVisitor*>(visitor))
    return parserVisitor->visitPlus(this);
  else
    return visitor->visitChildren(this);
}

CalcParser::ExprContext* CalcParser::expr() {
   return expr(0);
}

CalcParser::ExprContext* CalcParser::expr(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  CalcParser::ExprContext *_localctx = _tracker.createInstance<ExprContext>(_ctx, parentState);
  CalcParser::ExprContext *previousContext = _localctx;
  (void)previousContext; // Silence compiler, in case the context is not used by generated code.
  size_t startState = 4;
  enterRecursionRule(_localctx, 4, CalcParser::RuleExpr, precedence);

    size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    unrollRecursionContexts(parentContext);
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(99);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case CalcParser::NOT: {
        _localctx = _tracker.createInstance<NegationContext>(_localctx);
        _ctx = _localctx;
        previousContext = _localctx;

        setState(62);
        match(CalcParser::NOT);
        setState(63);
        expr(12);
        break;
      }

      case CalcParser::T__7: {
        _localctx = _tracker.createInstance<ParentesisContext>(_localctx);
        _ctx = _localctx;
        previousContext = _localctx;
        setState(64);
        match(CalcParser::T__7);
        setState(65);
        expr(0);
        setState(66);
        match(CalcParser::T__8);
        break;
      }

      case CalcParser::ABS: {
        _localctx = _tracker.createInstance<AbsValueContext>(_localctx);
        _ctx = _localctx;
        previousContext = _localctx;
        setState(68);
        match(CalcParser::ABS);
        setState(69);
        match(CalcParser::T__7);
        setState(70);
        expr(0);
        setState(71);
        match(CalcParser::T__8);
        break;
      }

      case CalcParser::FUN: {
        _localctx = _tracker.createInstance<FunctionsOperationsContext>(_localctx);
        _ctx = _localctx;
        previousContext = _localctx;
        setState(73);
        match(CalcParser::FUN);
        setState(74);
        match(CalcParser::T__7);
        setState(75);
        expr(0);
        setState(80);
        _errHandler->sync(this);
        _la = _input->LA(1);
        while (_la == CalcParser::T__9) {
          setState(76);
          match(CalcParser::T__9);
          setState(77);
          expr(0);
          setState(82);
          _errHandler->sync(this);
          _la = _input->LA(1);
        }
        setState(83);
        match(CalcParser::T__8);
        break;
      }

      case CalcParser::T__10: {
        _localctx = _tracker.createInstance<CondicionalCompactoContext>(_localctx);
        _ctx = _localctx;
        previousContext = _localctx;
        setState(85);
        match(CalcParser::T__10);
        setState(86);
        expr(0);
        setState(87);
        match(CalcParser::OPBIN);
        setState(88);
        expr(0);
        setState(89);
        match(CalcParser::T__11);
        setState(90);
        expr(0);
        setState(91);
        match(CalcParser::T__12);
        setState(92);
        expr(0);
        setState(93);
        match(CalcParser::T__13);
        break;
      }

      case CalcParser::SUB: {
        _localctx = _tracker.createInstance<UnaryMinusContext>(_localctx);
        _ctx = _localctx;
        previousContext = _localctx;
        setState(95);
        match(CalcParser::SUB);
        setState(96);
        match(CalcParser::ID);
        break;
      }

      case CalcParser::INT: {
        _localctx = _tracker.createInstance<IntContext>(_localctx);
        _ctx = _localctx;
        previousContext = _localctx;
        setState(97);
        match(CalcParser::INT);
        break;
      }

      case CalcParser::ID: {
        _localctx = _tracker.createInstance<IdContext>(_localctx);
        _ctx = _localctx;
        previousContext = _localctx;
        setState(98);
        match(CalcParser::ID);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
    _ctx->stop = _input->LT(-1);
    setState(115);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 9, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(113);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 8, _ctx)) {
        case 1: {
          auto newContext = _tracker.createInstance<ProdContext>(_tracker.createInstance<ExprContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleExpr);
          setState(101);

          if (!(precpred(_ctx, 10))) throw FailedPredicateException(this, "precpred(_ctx, 10)");
          setState(102);
          _la = _input->LA(1);
          if (!(_la == CalcParser::MUL

          || _la == CalcParser::DIV)) {
          _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(103);
          expr(11);
          break;
        }

        case 2: {
          auto newContext = _tracker.createInstance<PlusContext>(_tracker.createInstance<ExprContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleExpr);
          setState(104);

          if (!(precpred(_ctx, 9))) throw FailedPredicateException(this, "precpred(_ctx, 9)");
          setState(105);
          _la = _input->LA(1);
          if (!(_la == CalcParser::ADD

          || _la == CalcParser::SUB)) {
          _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(106);
          expr(10);
          break;
        }

        case 3: {
          auto newContext = _tracker.createInstance<OPBinContext>(_tracker.createInstance<ExprContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleExpr);
          setState(107);

          if (!(precpred(_ctx, 8))) throw FailedPredicateException(this, "precpred(_ctx, 8)");
          setState(108);
          match(CalcParser::OPBIN);
          setState(109);
          expr(9);
          break;
        }

        case 4: {
          auto newContext = _tracker.createInstance<LogicalOperationContext>(_tracker.createInstance<ExprContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleExpr);
          setState(110);

          if (!(precpred(_ctx, 7))) throw FailedPredicateException(this, "precpred(_ctx, 7)");
          setState(111);
          match(CalcParser::LOGIC);
          setState(112);
          expr(8);
          break;
        }

        default:
          break;
        } 
      }
      setState(117);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 9, _ctx);
    }
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }
  return _localctx;
}

bool CalcParser::sempred(RuleContext *context, size_t ruleIndex, size_t predicateIndex) {
  switch (ruleIndex) {
    case 2: return exprSempred(antlrcpp::downCast<ExprContext *>(context), predicateIndex);

  default:
    break;
  }
  return true;
}

bool CalcParser::exprSempred(ExprContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 0: return precpred(_ctx, 10);
    case 1: return precpred(_ctx, 9);
    case 2: return precpred(_ctx, 8);
    case 3: return precpred(_ctx, 7);

  default:
    break;
  }
  return true;
}

void CalcParser::initialize() {
#if ANTLR4_USE_THREAD_LOCAL_CACHE
  calcParserInitialize();
#else
  ::antlr4::internal::call_once(calcParserOnceFlag, calcParserInitialize);
#endif
}
