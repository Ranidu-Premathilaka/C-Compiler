grammar parser;

// Parser rules
prog:   stmt_list ;

stmt_list   :   stmt 
            |   stmt_list stmt
            ;

stmt        :   funcCall 
            |   declaration 
            ;

declaration :   type ID ASSIGN expr STMT_END
            ;

funcCall    :   ID L_PAREN args R_PAREN STMT_END
            |   ID L_PAREN R_PAREN STMT_END
            ;

args        :   term
            ;

term        :   literal 
            |   ID
            ;

literal     :   INT_LITERAL 
            ;
    
type        :   KW_INT
            ;

expr        :   term
            |   term (ADD_OP term)+
            ;



// Lexer rules
STMT_END:   ';' ;

KW_INT   :   'int' ;

ADD_OP   :   '+' ;

ID      :   [a-zA-Z_][a-zA-Z_0-9]* ;

INT_LITERAL     :   [0-9]+ ;

ASSIGN  :   '=' ;

L_PAREN :   '(' ;
R_PAREN :   ')' ;
WS      :   [\r\n \t]+ -> skip ;