#ifndef TOKEN_TYPE_H
#define TOKEN_TYPE_H

typedef enum{
    TOKEN_INVALID = -1,
    TOKEN_EOF,
    
    TOKEN_STMT_END,

    TOKEN_KW_INT,

    TOKEN_ADD_OP,

    TOKEN_ID,

    TOKEN_INT_LITERAL,

    TOKEN_ASSIGN,

    TOKEN_L_PAREN,
    TOKEN_R_PAREN,

} TOKEN_TYPE;

#endif