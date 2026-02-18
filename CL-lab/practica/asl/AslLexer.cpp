
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
      "T__0", "T__1", "T__2", "T__3", "ASSIGN", "EQUAL", "PLUS", "MINUS", 
      "MUL", "DIV", "VAR", "INT", "BOOL", "FLOAT", "CHAR", "IF", "THEN", 
      "ELSE", "ENDIF", "FUNC", "ENDFUNC", "READ", "WRITE", "ID", "INTVAL", 
      "STRING", "ESC_SEQ", "COMMENT", "WS"
    },
    std::vector<std::string>{
      "DEFAULT_TOKEN_CHANNEL", "HIDDEN"
    },
    std::vector<std::string>{
      "DEFAULT_MODE"
    },
    std::vector<std::string>{
      "", "'('", "')'", "':'", "';'", "'='", "'=='", "'+'", "'-'", "'*'", 
      "'/'", "'var'", "'int'", "'bool'", "'float'", "'char'", "'if'", "'then'", 
      "'else'", "'endif'", "'func'", "'endfunc'", "'read'", "'write'"
    },
    std::vector<std::string>{
      "", "", "", "", "", "ASSIGN", "EQUAL", "PLUS", "MINUS", "MUL", "DIV", 
      "VAR", "INT", "BOOL", "FLOAT", "CHAR", "IF", "THEN", "ELSE", "ENDIF", 
      "FUNC", "ENDFUNC", "READ", "WRITE", "ID", "INTVAL", "STRING", "COMMENT", 
      "WS"
    }
  );
  static const int32_t serializedATNSegment[] = {
  	4,0,28,207,6,-1,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,
  	6,2,7,7,7,2,8,7,8,2,9,7,9,2,10,7,10,2,11,7,11,2,12,7,12,2,13,7,13,2,14,
  	7,14,2,15,7,15,2,16,7,16,2,17,7,17,2,18,7,18,2,19,7,19,2,20,7,20,2,21,
  	7,21,2,22,7,22,2,23,7,23,2,24,7,24,2,25,7,25,2,26,7,26,2,27,7,27,2,28,
  	7,28,1,0,1,0,1,1,1,1,1,2,1,2,1,3,1,3,1,4,1,4,1,5,1,5,1,5,1,6,1,6,1,7,
  	1,7,1,8,1,8,1,9,1,9,1,10,1,10,1,10,1,10,1,11,1,11,1,11,1,11,1,12,1,12,
  	1,12,1,12,1,12,1,13,1,13,1,13,1,13,1,13,1,13,1,14,1,14,1,14,1,14,1,14,
  	1,15,1,15,1,15,1,16,1,16,1,16,1,16,1,16,1,17,1,17,1,17,1,17,1,17,1,18,
  	1,18,1,18,1,18,1,18,1,18,1,19,1,19,1,19,1,19,1,19,1,20,1,20,1,20,1,20,
  	1,20,1,20,1,20,1,20,1,21,1,21,1,21,1,21,1,21,1,22,1,22,1,22,1,22,1,22,
  	1,22,1,23,1,23,5,23,150,8,23,10,23,12,23,153,9,23,1,24,4,24,156,8,24,
  	11,24,12,24,157,1,25,1,25,1,25,5,25,163,8,25,10,25,12,25,166,9,25,1,25,
  	1,25,1,26,1,26,1,26,1,27,1,27,1,27,1,27,5,27,177,8,27,10,27,12,27,180,
  	9,27,1,27,3,27,183,8,27,1,27,1,27,1,27,1,27,1,27,5,27,190,8,27,10,27,
  	12,27,193,9,27,1,27,1,27,3,27,197,8,27,1,27,1,27,1,28,4,28,202,8,28,11,
  	28,12,28,203,1,28,1,28,1,191,0,29,1,1,3,2,5,3,7,4,9,5,11,6,13,7,15,8,
  	17,9,19,10,21,11,23,12,25,13,27,14,29,15,31,16,33,17,35,18,37,19,39,20,
  	41,21,43,22,45,23,47,24,49,25,51,26,53,0,55,27,57,28,1,0,6,2,0,65,90,
  	97,122,4,0,48,57,65,90,95,95,97,122,2,0,34,34,92,92,8,0,34,34,39,39,92,
  	92,98,98,102,102,110,110,114,114,116,116,2,0,10,10,13,13,3,0,9,10,13,
  	13,32,32,214,0,1,1,0,0,0,0,3,1,0,0,0,0,5,1,0,0,0,0,7,1,0,0,0,0,9,1,0,
  	0,0,0,11,1,0,0,0,0,13,1,0,0,0,0,15,1,0,0,0,0,17,1,0,0,0,0,19,1,0,0,0,
  	0,21,1,0,0,0,0,23,1,0,0,0,0,25,1,0,0,0,0,27,1,0,0,0,0,29,1,0,0,0,0,31,
  	1,0,0,0,0,33,1,0,0,0,0,35,1,0,0,0,0,37,1,0,0,0,0,39,1,0,0,0,0,41,1,0,
  	0,0,0,43,1,0,0,0,0,45,1,0,0,0,0,47,1,0,0,0,0,49,1,0,0,0,0,51,1,0,0,0,
  	0,55,1,0,0,0,0,57,1,0,0,0,1,59,1,0,0,0,3,61,1,0,0,0,5,63,1,0,0,0,7,65,
  	1,0,0,0,9,67,1,0,0,0,11,69,1,0,0,0,13,72,1,0,0,0,15,74,1,0,0,0,17,76,
  	1,0,0,0,19,78,1,0,0,0,21,80,1,0,0,0,23,84,1,0,0,0,25,88,1,0,0,0,27,93,
  	1,0,0,0,29,99,1,0,0,0,31,104,1,0,0,0,33,107,1,0,0,0,35,112,1,0,0,0,37,
  	117,1,0,0,0,39,123,1,0,0,0,41,128,1,0,0,0,43,136,1,0,0,0,45,141,1,0,0,
  	0,47,147,1,0,0,0,49,155,1,0,0,0,51,159,1,0,0,0,53,169,1,0,0,0,55,196,
  	1,0,0,0,57,201,1,0,0,0,59,60,5,40,0,0,60,2,1,0,0,0,61,62,5,41,0,0,62,
  	4,1,0,0,0,63,64,5,58,0,0,64,6,1,0,0,0,65,66,5,59,0,0,66,8,1,0,0,0,67,
  	68,5,61,0,0,68,10,1,0,0,0,69,70,5,61,0,0,70,71,5,61,0,0,71,12,1,0,0,0,
  	72,73,5,43,0,0,73,14,1,0,0,0,74,75,5,45,0,0,75,16,1,0,0,0,76,77,5,42,
  	0,0,77,18,1,0,0,0,78,79,5,47,0,0,79,20,1,0,0,0,80,81,5,118,0,0,81,82,
  	5,97,0,0,82,83,5,114,0,0,83,22,1,0,0,0,84,85,5,105,0,0,85,86,5,110,0,
  	0,86,87,5,116,0,0,87,24,1,0,0,0,88,89,5,98,0,0,89,90,5,111,0,0,90,91,
  	5,111,0,0,91,92,5,108,0,0,92,26,1,0,0,0,93,94,5,102,0,0,94,95,5,108,0,
  	0,95,96,5,111,0,0,96,97,5,97,0,0,97,98,5,116,0,0,98,28,1,0,0,0,99,100,
  	5,99,0,0,100,101,5,104,0,0,101,102,5,97,0,0,102,103,5,114,0,0,103,30,
  	1,0,0,0,104,105,5,105,0,0,105,106,5,102,0,0,106,32,1,0,0,0,107,108,5,
  	116,0,0,108,109,5,104,0,0,109,110,5,101,0,0,110,111,5,110,0,0,111,34,
  	1,0,0,0,112,113,5,101,0,0,113,114,5,108,0,0,114,115,5,115,0,0,115,116,
  	5,101,0,0,116,36,1,0,0,0,117,118,5,101,0,0,118,119,5,110,0,0,119,120,
  	5,100,0,0,120,121,5,105,0,0,121,122,5,102,0,0,122,38,1,0,0,0,123,124,
  	5,102,0,0,124,125,5,117,0,0,125,126,5,110,0,0,126,127,5,99,0,0,127,40,
  	1,0,0,0,128,129,5,101,0,0,129,130,5,110,0,0,130,131,5,100,0,0,131,132,
  	5,102,0,0,132,133,5,117,0,0,133,134,5,110,0,0,134,135,5,99,0,0,135,42,
  	1,0,0,0,136,137,5,114,0,0,137,138,5,101,0,0,138,139,5,97,0,0,139,140,
  	5,100,0,0,140,44,1,0,0,0,141,142,5,119,0,0,142,143,5,114,0,0,143,144,
  	5,105,0,0,144,145,5,116,0,0,145,146,5,101,0,0,146,46,1,0,0,0,147,151,
  	7,0,0,0,148,150,7,1,0,0,149,148,1,0,0,0,150,153,1,0,0,0,151,149,1,0,0,
  	0,151,152,1,0,0,0,152,48,1,0,0,0,153,151,1,0,0,0,154,156,2,48,57,0,155,
  	154,1,0,0,0,156,157,1,0,0,0,157,155,1,0,0,0,157,158,1,0,0,0,158,50,1,
  	0,0,0,159,164,5,34,0,0,160,163,3,53,26,0,161,163,8,2,0,0,162,160,1,0,
  	0,0,162,161,1,0,0,0,163,166,1,0,0,0,164,162,1,0,0,0,164,165,1,0,0,0,165,
  	167,1,0,0,0,166,164,1,0,0,0,167,168,5,34,0,0,168,52,1,0,0,0,169,170,5,
  	92,0,0,170,171,7,3,0,0,171,54,1,0,0,0,172,173,5,47,0,0,173,174,5,47,0,
  	0,174,178,1,0,0,0,175,177,8,4,0,0,176,175,1,0,0,0,177,180,1,0,0,0,178,
  	176,1,0,0,0,178,179,1,0,0,0,179,182,1,0,0,0,180,178,1,0,0,0,181,183,5,
  	13,0,0,182,181,1,0,0,0,182,183,1,0,0,0,183,184,1,0,0,0,184,197,5,10,0,
  	0,185,186,5,47,0,0,186,187,5,42,0,0,187,191,1,0,0,0,188,190,9,0,0,0,189,
  	188,1,0,0,0,190,193,1,0,0,0,191,192,1,0,0,0,191,189,1,0,0,0,192,194,1,
  	0,0,0,193,191,1,0,0,0,194,195,5,42,0,0,195,197,5,47,0,0,196,172,1,0,0,
  	0,196,185,1,0,0,0,197,198,1,0,0,0,198,199,6,27,0,0,199,56,1,0,0,0,200,
  	202,7,5,0,0,201,200,1,0,0,0,202,203,1,0,0,0,203,201,1,0,0,0,203,204,1,
  	0,0,0,204,205,1,0,0,0,205,206,6,28,0,0,206,58,1,0,0,0,10,0,151,157,162,
  	164,178,182,191,196,203,1,6,0,0
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
