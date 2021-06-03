grammar Grammar;

// Parser rules

compilationUnit
    : classDeclaration EOF
    ;

classDeclaration
    : CLASS IDENTIFIER '{' methodDeclaration* '}'
    ;

methodDeclaration
    : DEF IDENTIFIER '{' instructionsDecl '}'
    ;

instructionsDecl
    : (instruction | (ifBlock elseBlock?) ) instructionsDecl?
    ;

instruction
    : (IADD | ISUB | IDIV | IMUL | IRET)
    | (FADD | FSUB | FDIV | FMUL | FRET)
    | (OR | AND)
    | CMPEQ
    | SWAP
    | RET
    | call
    | instructionsWithOp
    ;

call
    : CALL IDENTIFIER '::' IDENTIFIER;

ifBlock
    : IF  '{' instructionsDecl '}'
    ;

elseBlock
    : ELSE  '{' instructionsDecl '}'
    ;

instructionsWithOp
    : IPUSH DECIMAL_LITERAL
    | ILOAD DECIMAL_LITERAL
    | ISTORE DECIMAL_LITERAL
    | FPUSH FLOAT_LITERAL
    | FLOAD DECIMAL_LITERAL
    | FSTORE DECIMAL_LITERAL
    | LDC STRING_LITERAL
    | RSTORE DECIMAL_LITERAL
    ;

// Lexer rules

IADD     : 'iadd';
ISUB     : 'isub';
IDIV     : 'idiv';
IMUL     : 'imul';
IPUSH    : 'ipush';
IPOP     : 'ipop';
ILOAD    : 'iload';
ISTORE   : 'istore';
IRET     : 'iret';

FADD     : 'fadd';
FSUB     : 'fsub';
FDIV     : 'fdiv';
FMUL     : 'fmul';
FPUSH    : 'fpush';
FPOP     : 'fpop';
FLOAD    : 'fload';
FSTORE   : 'fstore';
FRET     : 'fret';
LDC      : 'ldc';
SWAP     : 'swap';


AND      : 'and';
OR       : 'or';

RSTORE   : 'rstore';
CMPEQ    : 'cmpeq';

CLASS       : 'class';
DEF         : 'def';
IF          : 'if';
ELSE        : 'else';
CALL        : 'call';
RET         : 'ret';

NEWLINE     : ('\r'? '\n' | '\r')+ -> skip ;

TAB         : ('\t' | '        ' | '    ' ) -> skip;

WHITESPACE  : ' ' -> skip ;

DECIMAL_LITERAL:    ('0' | [1-9] (Digits? | '_'+ Digits)) [lL]?;

FLOAT_LITERAL:      (Digits '.' Digits? | '.' Digits)
             ;

BOOL_LITERAL:       'true'
            |       'false'
            ;

CHAR_LITERAL:       '\'' (~['\\\r\n] | EscapeSequence) '\'';

STRING_LITERAL:     '"' (~["\\\r\n] | EscapeSequence)* '"';

IDENTIFIER:         Letter LetterOrDigit*;

fragment LetterOrDigit
    : Letter
    | [0-9]
    ;
fragment Letter
    : [a-zA-Z$_]
    ;

fragment EscapeSequence
    : '\\' [btnfr"'\\]
    | '\\' ([0-3]? [0-7])? [0-7]
    ;

fragment Digits
    : [0-9] ([0-9_]* [0-9])?
    ;
