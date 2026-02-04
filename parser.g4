grammar parser;

// Parser rules
prog:   stmt_list ;

stmt_list   :   stmt 
            |   stmt stmt_list
            ;

stmt        :   funcCall 
            |   declaration 
            ;

declaration :   type ID ASSIGN expr STMT_END
            |   type ID STMT_END
            ;

funcCall    :   ID L_PAREN args R_PAREN STMT_END
            |   ID L_PAREN R_PAREN STMT_END
            ;

args        :   term
            |   term ARG_SEPARATOR args
            ;

term        :   literal 
            |   ID
            ;

literal     :   INT_LITERAL 
            |   STRING_LITERAL
            |   CHAR_LITERAL 
            ;
    
type        :   KW_INT
            |   KW_CHAR
            |   KW_FLOAT
            ;

expr        :   term
            |   term ADD_OP expr
            ;



// Lexer rules
STMT_END:   ';' ;

KW_INT   :   'int' ;
KW_CHAR  :   'char' ;
KW_FLOAT :   'float' ;

SUB_OP   :   '-' ;
ADD_OP   :   '+' ;

ID      :   [a-zA-Z_][a-zA-Z_0-9]* ;

INT_LITERAL     :   [0-9]+ ;
STRING_LITERAL  :   '"' [^"]* '"' ;
CHAR_LITERAL    :   '\'' [^'] '\'';

ASSIGN  :   '=' ;

L_PAREN :   '(' ;
R_PAREN :   ')' ;

ARG_SEPARATOR   :   ',';

WS      :   [\r\n \t]+ -> skip ;