
// Generated from Calc.g4 by ANTLR 4.13.2


#include "CalcLexer.h"


using namespace antlr4;



using namespace antlr4;

namespace {

struct CalcLexerStaticData final {
  CalcLexerStaticData(std::vector<std::string> ruleNames,
                          std::vector<std::string> channelNames,
                          std::vector<std::string> modeNames,
                          std::vector<std::string> literalNames,
                          std::vector<std::string> symbolicNames)
      : ruleNames(std::move(ruleNames)), channelNames(std::move(channelNames)),
        modeNames(std::move(modeNames)), literalNames(std::move(literalNames)),
        symbolicNames(std::move(symbolicNames)),
        vocabulary(this->literalNames, this->symbolicNames) {}

  CalcLexerStaticData(const CalcLexerStaticData&) = delete;
  CalcLexerStaticData(CalcLexerStaticData&&) = delete;
  CalcLexerStaticData& operator=(const CalcLexerStaticData&) = delete;
  CalcLexerStaticData& operator=(CalcLexerStaticData&&) = delete;

  std::vector<antlr4::dfa::DFA> decisionToDFA;
  antlr4::atn::PredictionContextCache sharedContextCache;
  const std::vector<std::string> ruleNames;
  const std::vector<std::string> channelNames;
  const std::vector<std::string> modeNames;
  const std::vector<std::string> literalNames;
  const std::vector<std::string> symbolicNames;
  const antlr4::dfa::Vocabulary vocabulary;
  antlr4::atn::SerializedATNView serializedATN;
  std::unique_ptr<antlr4::atn::ATN> atn;
};

::antlr4::internal::OnceFlag calclexerLexerOnceFlag;
#if ANTLR4_USE_THREAD_LOCAL_CACHE
static thread_local
#endif
std::unique_ptr<CalcLexerStaticData> calclexerLexerStaticData = nullptr;

void calclexerLexerInitialize() {
#if ANTLR4_USE_THREAD_LOCAL_CACHE
  if (calclexerLexerStaticData != nullptr) {
    return;
  }
#else
  assert(calclexerLexerStaticData == nullptr);
#endif
  auto staticData = std::make_unique<CalcLexerStaticData>(
    std::vector<std::string>{
      "T__0", "T__1", "T__2", "T__3", "T__4", "T__5", "T__6", "T__7", "T__8", 
      "T__9", "T__10", "T__11", "T__12", "T__13", "ABS", "FUN", "MUL", "DIV", 
      "ADD", "SUB", "NOT", "LOGIC", "OPBIN", "ID", "INT", "NEWLINE", "WS"
    },
    std::vector<std::string>{
      "DEFAULT_TOKEN_CHANNEL", "HIDDEN"
    },
    std::vector<std::string>{
      "DEFAULT_MODE"
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
  	4,0,27,178,6,-1,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,
  	6,2,7,7,7,2,8,7,8,2,9,7,9,2,10,7,10,2,11,7,11,2,12,7,12,2,13,7,13,2,14,
  	7,14,2,15,7,15,2,16,7,16,2,17,7,17,2,18,7,18,2,19,7,19,2,20,7,20,2,21,
  	7,21,2,22,7,22,2,23,7,23,2,24,7,24,2,25,7,25,2,26,7,26,1,0,1,0,1,0,1,
  	1,1,1,1,1,1,1,1,1,1,1,1,2,1,2,1,2,1,2,1,2,1,3,1,3,1,3,1,3,1,3,1,3,1,3,
  	1,3,1,4,1,4,1,4,1,4,1,4,1,4,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,6,1,
  	6,1,7,1,7,1,8,1,8,1,9,1,9,1,10,1,10,1,11,1,11,1,12,1,12,1,13,1,13,1,14,
  	1,14,1,14,1,14,1,15,1,15,1,15,1,15,1,15,1,15,1,15,1,15,1,15,1,15,1,15,
  	1,15,3,15,125,8,15,1,16,1,16,1,17,1,17,1,18,1,18,1,19,1,19,1,20,1,20,
  	1,20,1,20,1,21,1,21,1,21,1,21,1,21,3,21,144,8,21,1,22,1,22,1,22,1,22,
  	1,22,1,22,1,22,1,22,1,22,3,22,155,8,22,1,23,4,23,158,8,23,11,23,12,23,
  	159,1,24,4,24,163,8,24,11,24,12,24,164,1,25,3,25,168,8,25,1,25,1,25,1,
  	26,4,26,173,8,26,11,26,12,26,174,1,26,1,26,0,0,27,1,1,3,2,5,3,7,4,9,5,
  	11,6,13,7,15,8,17,9,19,10,21,11,23,12,25,13,27,14,29,15,31,16,33,17,35,
  	18,37,19,39,20,41,21,43,22,45,23,47,24,49,25,51,26,53,27,1,0,4,2,0,60,
  	60,62,62,2,0,65,90,97,122,1,0,48,57,2,0,9,9,32,32,189,0,1,1,0,0,0,0,3,
  	1,0,0,0,0,5,1,0,0,0,0,7,1,0,0,0,0,9,1,0,0,0,0,11,1,0,0,0,0,13,1,0,0,0,
  	0,15,1,0,0,0,0,17,1,0,0,0,0,19,1,0,0,0,0,21,1,0,0,0,0,23,1,0,0,0,0,25,
  	1,0,0,0,0,27,1,0,0,0,0,29,1,0,0,0,0,31,1,0,0,0,0,33,1,0,0,0,0,35,1,0,
  	0,0,0,37,1,0,0,0,0,39,1,0,0,0,0,41,1,0,0,0,0,43,1,0,0,0,0,45,1,0,0,0,
  	0,47,1,0,0,0,0,49,1,0,0,0,0,51,1,0,0,0,0,53,1,0,0,0,1,55,1,0,0,0,3,58,
  	1,0,0,0,5,64,1,0,0,0,7,69,1,0,0,0,9,77,1,0,0,0,11,83,1,0,0,0,13,92,1,
  	0,0,0,15,94,1,0,0,0,17,96,1,0,0,0,19,98,1,0,0,0,21,100,1,0,0,0,23,102,
  	1,0,0,0,25,104,1,0,0,0,27,106,1,0,0,0,29,108,1,0,0,0,31,124,1,0,0,0,33,
  	126,1,0,0,0,35,128,1,0,0,0,37,130,1,0,0,0,39,132,1,0,0,0,41,134,1,0,0,
  	0,43,143,1,0,0,0,45,154,1,0,0,0,47,157,1,0,0,0,49,162,1,0,0,0,51,167,
  	1,0,0,0,53,172,1,0,0,0,55,56,5,73,0,0,56,57,5,70,0,0,57,2,1,0,0,0,58,
  	59,5,69,0,0,59,60,5,78,0,0,60,61,5,68,0,0,61,62,5,73,0,0,62,63,5,70,0,
  	0,63,4,1,0,0,0,64,65,5,69,0,0,65,66,5,76,0,0,66,67,5,83,0,0,67,68,5,69,
  	0,0,68,6,1,0,0,0,69,70,5,69,0,0,70,71,5,78,0,0,71,72,5,68,0,0,72,73,5,
  	69,0,0,73,74,5,76,0,0,74,75,5,83,0,0,75,76,5,69,0,0,76,8,1,0,0,0,77,78,
  	5,87,0,0,78,79,5,72,0,0,79,80,5,73,0,0,80,81,5,76,0,0,81,82,5,69,0,0,
  	82,10,1,0,0,0,83,84,5,69,0,0,84,85,5,78,0,0,85,86,5,68,0,0,86,87,5,87,
  	0,0,87,88,5,72,0,0,88,89,5,73,0,0,89,90,5,76,0,0,90,91,5,69,0,0,91,12,
  	1,0,0,0,92,93,5,61,0,0,93,14,1,0,0,0,94,95,5,40,0,0,95,16,1,0,0,0,96,
  	97,5,41,0,0,97,18,1,0,0,0,98,99,5,44,0,0,99,20,1,0,0,0,100,101,5,91,0,
  	0,101,22,1,0,0,0,102,103,5,63,0,0,103,24,1,0,0,0,104,105,5,58,0,0,105,
  	26,1,0,0,0,106,107,5,93,0,0,107,28,1,0,0,0,108,109,5,97,0,0,109,110,5,
  	98,0,0,110,111,5,115,0,0,111,30,1,0,0,0,112,113,5,112,0,0,113,114,5,111,
  	0,0,114,125,5,119,0,0,115,116,5,109,0,0,116,117,5,97,0,0,117,125,5,120,
  	0,0,118,119,5,109,0,0,119,120,5,105,0,0,120,125,5,110,0,0,121,122,5,115,
  	0,0,122,123,5,117,0,0,123,125,5,109,0,0,124,112,1,0,0,0,124,115,1,0,0,
  	0,124,118,1,0,0,0,124,121,1,0,0,0,125,32,1,0,0,0,126,127,5,42,0,0,127,
  	34,1,0,0,0,128,129,5,47,0,0,129,36,1,0,0,0,130,131,5,43,0,0,131,38,1,
  	0,0,0,132,133,5,45,0,0,133,40,1,0,0,0,134,135,5,110,0,0,135,136,5,111,
  	0,0,136,137,5,116,0,0,137,42,1,0,0,0,138,139,5,97,0,0,139,140,5,110,0,
  	0,140,144,5,100,0,0,141,142,5,111,0,0,142,144,5,114,0,0,143,138,1,0,0,
  	0,143,141,1,0,0,0,144,44,1,0,0,0,145,155,7,0,0,0,146,147,5,61,0,0,147,
  	155,5,61,0,0,148,149,5,33,0,0,149,155,5,61,0,0,150,151,5,62,0,0,151,155,
  	5,61,0,0,152,153,5,60,0,0,153,155,5,61,0,0,154,145,1,0,0,0,154,146,1,
  	0,0,0,154,148,1,0,0,0,154,150,1,0,0,0,154,152,1,0,0,0,155,46,1,0,0,0,
  	156,158,7,1,0,0,157,156,1,0,0,0,158,159,1,0,0,0,159,157,1,0,0,0,159,160,
  	1,0,0,0,160,48,1,0,0,0,161,163,7,2,0,0,162,161,1,0,0,0,163,164,1,0,0,
  	0,164,162,1,0,0,0,164,165,1,0,0,0,165,50,1,0,0,0,166,168,5,13,0,0,167,
  	166,1,0,0,0,167,168,1,0,0,0,168,169,1,0,0,0,169,170,5,10,0,0,170,52,1,
  	0,0,0,171,173,7,3,0,0,172,171,1,0,0,0,173,174,1,0,0,0,174,172,1,0,0,0,
  	174,175,1,0,0,0,175,176,1,0,0,0,176,177,6,26,0,0,177,54,1,0,0,0,8,0,124,
  	143,154,159,164,167,174,1,6,0,0
  };
  staticData->serializedATN = antlr4::atn::SerializedATNView(serializedATNSegment, sizeof(serializedATNSegment) / sizeof(serializedATNSegment[0]));

  antlr4::atn::ATNDeserializer deserializer;
  staticData->atn = deserializer.deserialize(staticData->serializedATN);

  const size_t count = staticData->atn->getNumberOfDecisions();
  staticData->decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    staticData->decisionToDFA.emplace_back(staticData->atn->getDecisionState(i), i);
  }
  calclexerLexerStaticData = std::move(staticData);
}

}

CalcLexer::CalcLexer(CharStream *input) : Lexer(input) {
  CalcLexer::initialize();
  _interpreter = new atn::LexerATNSimulator(this, *calclexerLexerStaticData->atn, calclexerLexerStaticData->decisionToDFA, calclexerLexerStaticData->sharedContextCache);
}

CalcLexer::~CalcLexer() {
  delete _interpreter;
}

std::string CalcLexer::getGrammarFileName() const {
  return "Calc.g4";
}

const std::vector<std::string>& CalcLexer::getRuleNames() const {
  return calclexerLexerStaticData->ruleNames;
}

const std::vector<std::string>& CalcLexer::getChannelNames() const {
  return calclexerLexerStaticData->channelNames;
}

const std::vector<std::string>& CalcLexer::getModeNames() const {
  return calclexerLexerStaticData->modeNames;
}

const dfa::Vocabulary& CalcLexer::getVocabulary() const {
  return calclexerLexerStaticData->vocabulary;
}

antlr4::atn::SerializedATNView CalcLexer::getSerializedATN() const {
  return calclexerLexerStaticData->serializedATN;
}

const atn::ATN& CalcLexer::getATN() const {
  return *calclexerLexerStaticData->atn;
}




void CalcLexer::initialize() {
#if ANTLR4_USE_THREAD_LOCAL_CACHE
  calclexerLexerInitialize();
#else
  ::antlr4::internal::call_once(calclexerLexerOnceFlag, calclexerLexerInitialize);
#endif
}
