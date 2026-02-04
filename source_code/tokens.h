typedef enum{
    TOKEN_INVALID = -1,
    TOKEN_STMT_END,

    TOKEN_KW_INT,
    //TOKEN_KW_CHAR,
    //TOKEN_KW_FLOAT,

    //TOKEN_SUB_OP,
    TOKEN_ADD_OP,

    TOKEN_ID,

    TOKEN_INT_LITERAL,
    //TOKEN_CHAR_LITERAL,
    //TOKEN_STRING_LITERAL,

    TOKEN_ASSIGN,

    TOKEN_L_PAREN,
    TOKEN_R_PAREN,

    //TOKEN_ARG_SEPARATOR,
} TOKEN_TYPE;

typedef struct{
    TOKEN_TYPE type;
    char* value;
    int length;
} token;

token popNextToken();
token lookaheadNextToken();
void initializeLexer(const char* sourceCode);

