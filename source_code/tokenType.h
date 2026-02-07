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

static const char *tokenTypeToString(TOKEN_TYPE type) {
    switch (type) {
        case TOKEN_EOF: return "EOF";
        case TOKEN_STMT_END: return "STMT_END";
        case TOKEN_KW_INT: return "KW_INT";
        case TOKEN_ADD_OP: return "ADD_OP";
        case TOKEN_ID: return "ID";
        case TOKEN_INT_LITERAL: return "INT_LITERAL";
        case TOKEN_ASSIGN: return "ASSIGN";
        case TOKEN_L_PAREN: return "L_PAREN";
        case TOKEN_R_PAREN: return "R_PAREN";
        default: return "INVALID";
    }
}

#endif