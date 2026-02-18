
// Generated from Asl.g4 by ANTLR 4.13.2


#include "AslLexer.h"


using namespace antlr4;



using namespace antlr4;

namespace {

struct AslLexerStaticData final {
  AslLexerStaticData(std::vector<std::string> ruleNames,
                          std::vector<std::string> channelNames,
                          std::vector<std::string> modeNames,
                          std::vector<std::string> literalNames,
                          std::vector<std::string> symbolicNames)
      : ruleNames(std::move(ruleNames)), channelNames(std::move(channelNames)),
        modeNames(std::move(modeNames)), literalNames(std::move(literalNames)),
        symbolicNames(std::move(symbolicNames)),
        vocabulary(this->literalNames, this->symbolicNames) {}

  AslLexerStaticData(const AslLexerStaticData&) = delete;
  AslLexerStaticData(AslLexerStaticData&&) = delete;
  AslLexerStaticData& operator=(const AslLexerStaticData&) = delete;
  AslLexerStaticData& operator=(AslLexerStaticData&&) = delete;

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

::antlr4::internal::OnceFlag asllexerLexerOnceFlag;
#if ANTLR4_USE_THREAD_LOCAL_CACHE
static thread_local
#endif
std::unique_ptr<AslLexerStaticData> asllexerLexerStaticData = nullptr;

void asllexerLexerInitialize() {
#if ANTLR4_USE_THREAD_LOCAL_CACHE
  if (asllexerLexerStaticData != nullptr) {
    return;
  }
#else
  assert(asllexerLexerStaticData == nullptr);
#endif
  auto staticData = std::make_unique<AslLexerStaticData>(
    std::vector<std::string>{
      "T__0", "T__1", "T__2", "T__3", "ASSIGN", "EQUAL", "PLUS", "MUL", 
      "VAR", "INT", "BOOL", "IF", "THEN", "ELSE", "ENDIF", "FUNC", "ENDFUNC", 
      "READ", "WRITE", "ID", "INTVAL", "STRING", "ESC_SEQ", "COMMENT", "WS"
    },
    std::vector<std::string>{
      "DEFAULT_TOKEN_CHANNEL", "HIDDEN"
    },
    std::vector<std::string>{
      "DEFAULT_MODE"
    },
    std::vector<std::string>{
      "", "'('", "')'", "':'", "';'", "'='", "'=='", "'+'", "'*'", "'var'", 
      "'int'", "'bool'", "'if'", "'then'", "'else'", "'endif'", "'func'", 
      "'endfunc'", "'read'", "'write'"
    },
    std::vector<std::string>{
      "", "", "", "", "", "ASSIGN", "EQUAL", "PLUS", "MUL", "VAR", "INT", 
      "BOOL", "IF", "THEN", "ELSE", "ENDIF", "FUNC", "ENDFUNC", "READ", 
      "WRITE", "ID", "INTVAL", "STRING", "COMMENT", "WS"
    }
  );
  static const int32_t serializedATNSegment[] = {
  	4,0,24,184,6,-1,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,
  	6,2,7,7,7,2,8,7,8,2,9,7,9,2,10,7,10,2,11,7,11,2,12,7,12,2,13,7,13,2,14,
  	7,14,2,15,7,15,2,16,7,16,2,17,7,17,2,18,7,18,2,19,7,19,2,20,7,20,2,21,
  	7,21,2,22,7,22,2,23,7,23,2,24,7,24,1,0,1,0,1,1,1,1,1,2,1,2,1,3,1,3,1,
  	4,1,4,1,5,1,5,1,5,1,6,1,6,1,7,1,7,1,8,1,8,1,8,1,8,1,9,1,9,1,9,1,9,1,10,
  	1,10,1,10,1,10,1,10,1,11,1,11,1,11,1,12,1,12,1,12,1,12,1,12,1,13,1,13,
  	1,13,1,13,1,13,1,14,1,14,1,14,1,14,1,14,1,14,1,15,1,15,1,15,1,15,1,15,
  	1,16,1,16,1,16,1,16,1,16,1,16,1,16,1,16,1,17,1,17,1,17,1,17,1,17,1,18,
  	1,18,1,18,1,18,1,18,1,18,1,19,1,19,5,19,127,8,19,10,19,12,19,130,9,19,
  	1,20,4,20,133,8,20,11,20,12,20,134,1,21,1,21,1,21,5,21,140,8,21,10,21,
  	12,21,143,9,21,1,21,1,21,1,22,1,22,1,22,1,23,1,23,1,23,1,23,5,23,154,
  	8,23,10,23,12,23,157,9,23,1,23,3,23,160,8,23,1,23,1,23,1,23,1,23,1,23,
  	5,23,167,8,23,10,23,12,23,170,9,23,1,23,1,23,3,23,174,8,23,1,23,1,23,
  	1,24,4,24,179,8,24,11,24,12,24,180,1,24,1,24,1,168,0,25,1,1,3,2,5,3,7,
  	4,9,5,11,6,13,7,15,8,17,9,19,10,21,11,23,12,25,13,27,14,29,15,31,16,33,
  	17,35,18,37,19,39,20,41,21,43,22,45,0,47,23,49,24,1,0,6,2,0,65,90,97,
  	122,4,0,48,57,65,90,95,95,97,122,2,0,34,34,92,92,8,0,34,34,39,39,92,92,
  	98,98,102,102,110,110,114,114,116,116,2,0,10,10,13,13,3,0,9,10,13,13,
  	32,32,191,0,1,1,0,0,0,0,3,1,0,0,0,0,5,1,0,0,0,0,7,1,0,0,0,0,9,1,0,0,0,
  	0,11,1,0,0,0,0,13,1,0,0,0,0,15,1,0,0,0,0,17,1,0,0,0,0,19,1,0,0,0,0,21,
  	1,0,0,0,0,23,1,0,0,0,0,25,1,0,0,0,0,27,1,0,0,0,0,29,1,0,0,0,0,31,1,0,
  	0,0,0,33,1,0,0,0,0,35,1,0,0,0,0,37,1,0,0,0,0,39,1,0,0,0,0,41,1,0,0,0,
  	0,43,1,0,0,0,0,47,1,0,0,0,0,49,1,0,0,0,1,51,1,0,0,0,3,53,1,0,0,0,5,55,
  	1,0,0,0,7,57,1,0,0,0,9,59,1,0,0,0,11,61,1,0,0,0,13,64,1,0,0,0,15,66,1,
  	0,0,0,17,68,1,0,0,0,19,72,1,0,0,0,21,76,1,0,0,0,23,81,1,0,0,0,25,84,1,
  	0,0,0,27,89,1,0,0,0,29,94,1,0,0,0,31,100,1,0,0,0,33,105,1,0,0,0,35,113,
  	1,0,0,0,37,118,1,0,0,0,39,124,1,0,0,0,41,132,1,0,0,0,43,136,1,0,0,0,45,
  	146,1,0,0,0,47,173,1,0,0,0,49,178,1,0,0,0,51,52,5,40,0,0,52,2,1,0,0,0,
  	53,54,5,41,0,0,54,4,1,0,0,0,55,56,5,58,0,0,56,6,1,0,0,0,57,58,5,59,0,
  	0,58,8,1,0,0,0,59,60,5,61,0,0,60,10,1,0,0,0,61,62,5,61,0,0,62,63,5,61,
  	0,0,63,12,1,0,0,0,64,65,5,43,0,0,65,14,1,0,0,0,66,67,5,42,0,0,67,16,1,
  	0,0,0,68,69,5,118,0,0,69,70,5,97,0,0,70,71,5,114,0,0,71,18,1,0,0,0,72,
  	73,5,105,0,0,73,74,5,110,0,0,74,75,5,116,0,0,75,20,1,0,0,0,76,77,5,98,
  	0,0,77,78,5,111,0,0,78,79,5,111,0,0,79,80,5,108,0,0,80,22,1,0,0,0,81,
  	82,5,105,0,0,82,83,5,102,0,0,83,24,1,0,0,0,84,85,5,116,0,0,85,86,5,104,
  	0,0,86,87,5,101,0,0,87,88,5,110,0,0,88,26,1,0,0,0,89,90,5,101,0,0,90,
  	91,5,108,0,0,91,92,5,115,0,0,92,93,5,101,0,0,93,28,1,0,0,0,94,95,5,101,
  	0,0,95,96,5,110,0,0,96,97,5,100,0,0,97,98,5,105,0,0,98,99,5,102,0,0,99,
  	30,1,0,0,0,100,101,5,102,0,0,101,102,5,117,0,0,102,103,5,110,0,0,103,
  	104,5,99,0,0,104,32,1,0,0,0,105,106,5,101,0,0,106,107,5,110,0,0,107,108,
  	5,100,0,0,108,109,5,102,0,0,109,110,5,117,0,0,110,111,5,110,0,0,111,112,
  	5,99,0,0,112,34,1,0,0,0,113,114,5,114,0,0,114,115,5,101,0,0,115,116,5,
  	97,0,0,116,117,5,100,0,0,117,36,1,0,0,0,118,119,5,119,0,0,119,120,5,114,
  	0,0,120,121,5,105,0,0,121,122,5,116,0,0,122,123,5,101,0,0,123,38,1,0,
  	0,0,124,128,7,0,0,0,125,127,7,1,0,0,126,125,1,0,0,0,127,130,1,0,0,0,128,
  	126,1,0,0,0,128,129,1,0,0,0,129,40,1,0,0,0,130,128,1,0,0,0,131,133,2,
  	48,57,0,132,131,1,0,0,0,133,134,1,0,0,0,134,132,1,0,0,0,134,135,1,0,0,
  	0,135,42,1,0,0,0,136,141,5,34,0,0,137,140,3,45,22,0,138,140,8,2,0,0,139,
  	137,1,0,0,0,139,138,1,0,0,0,140,143,1,0,0,0,141,139,1,0,0,0,141,142,1,
  	0,0,0,142,144,1,0,0,0,143,141,1,0,0,0,144,145,5,34,0,0,145,44,1,0,0,0,
  	146,147,5,92,0,0,147,148,7,3,0,0,148,46,1,0,0,0,149,150,5,47,0,0,150,
  	151,5,47,0,0,151,155,1,0,0,0,152,154,8,4,0,0,153,152,1,0,0,0,154,157,
  	1,0,0,0,155,153,1,0,0,0,155,156,1,0,0,0,156,159,1,0,0,0,157,155,1,0,0,
  	0,158,160,5,13,0,0,159,158,1,0,0,0,159,160,1,0,0,0,160,161,1,0,0,0,161,
  	174,5,10,0,0,162,163,5,47,0,0,163,164,5,42,0,0,164,168,1,0,0,0,165,167,
  	9,0,0,0,166,165,1,0,0,0,167,170,1,0,0,0,168,169,1,0,0,0,168,166,1,0,0,
  	0,169,171,1,0,0,0,170,168,1,0,0,0,171,172,5,42,0,0,172,174,5,47,0,0,173,
  	149,1,0,0,0,173,162,1,0,0,0,174,175,1,0,0,0,175,176,6,23,0,0,176,48,1,
  	0,0,0,177,179,7,5,0,0,178,177,1,0,0,0,179,180,1,0,0,0,180,178,1,0,0,0,
  	180,181,1,0,0,0,181,182,1,0,0,0,182,183,6,24,0,0,183,50,1,0,0,0,10,0,
  	128,134,139,141,155,159,168,173,180,1,6,0,0
  };
  staticData->serializedATN = antlr4::atn::SerializedATNView(serializedATNSegment, sizeof(serializedATNSegment) / sizeof(serializedATNSegment[0]));

  antlr4::atn::ATNDeserializer deserializer;
  staticData->atn = deserializer.deserialize(staticData->serializedATN);

  const size_t count = staticData->atn->getNumberOfDecisions();
  staticData->decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    staticData->decisionToDFA.emplace_back(staticData->atn->getDecisionState(i), i);
  }
  asllexerLexerStaticData = std::move(staticData);
}

}

AslLexer::AslLexer(CharStream *input) : Lexer(input) {
  AslLexer::initialize();
  _interpreter = new atn::LexerATNSimulator(this, *asllexerLexerStaticData->atn, asllexerLexerStaticData->decisionToDFA, asllexerLexerStaticData->sharedContextCache);
}

AslLexer::~AslLexer() {
  delete _interpreter;
}

std::string AslLexer::getGrammarFileName() const {
  return "Asl.g4";
}

const std::vector<std::string>& AslLexer::getRuleNames() const {
  return asllexerLexerStaticData->ruleNames;
}

const std::vector<std::string>& AslLexer::getChannelNames() const {
  return asllexerLexerStaticData->channelNames;
}

const std::vector<std::string>& AslLexer::getModeNames() const {
  return asllexerLexerStaticData->modeNames;
}

const dfa::Vocabulary& AslLexer::getVocabulary() const {
  return asllexerLexerStaticData->vocabulary;
}

antlr4::atn::SerializedATNView AslLexer::getSerializedATN() const {
  return asllexerLexerStaticData->serializedATN;
}

const atn::ATN& AslLexer::getATN() const {
  return *asllexerLexerStaticData->atn;
}




void AslLexer::initialize() {
#if ANTLR4_USE_THREAD_LOCAL_CACHE
  asllexerLexerInitialize();
#else
  ::antlr4::internal::call_once(asllexerLexerOnceFlag, asllexerLexerInitialize);
#endif
}
