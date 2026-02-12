grammar Calc;

prog:  stat+ EOF ;

stat:  expr NEWLINE           # printExpr
    |  ID '=' expr NEWLINE    # assign
    |  NEWLINE                # blank
    ;

expr:  NOT expr                    # negation
    |  '(' expr ')'                # parentesis
    |  expr (MUL|DIV) expr         # prod
    |  expr (ADD|SUB) expr         # plus
    |  expr OPBIN expr             # OPBin
    |  expr LOGIC expr             # logicalOperation
    |  ABS '(' expr ')'            # absValue
    |  FUN '(' expr (',' expr)*')' # functionsOperations
    | '[' expr OPBIN expr '?' expr ':' expr ']' # condicionalCompacto
    |  SUB ID                      # unaryMinus
    |  INT                         # int
    |  ID                          # id
    ;


ABS   : 'abs';
FUN   :  ('pow' | 'max' | 'min' | 'sum');
MUL   :  '*' ;
DIV   :  '/' ;
ADD   :  '+' ;
SUB   :  '-' ;
NOT   :  'not';
LOGIC :  ('and' | 'or');
OPBIN :  ('>' | '<' | '==' | '!=' | '>=' | '<=');
ID    :  [a-zA-Z]+ ;       // match identifiers
INT   :  [0-9]+ ;          // match integers
NEWLINE: '\r'? '\n' ;    // return newlines to parser (is end-statement signal)
WS    :  [ \t]+ -> skip ;  // toss out whitespace
