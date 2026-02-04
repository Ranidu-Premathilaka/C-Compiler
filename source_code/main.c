#include "lexer.h"
#include <stdio.h>

int main(){

    FILE *sourceCode = fopen("test.txt", "rb");

    initializeLexer(sourceCode);
    token tok;
    do{
        tok = popCurrentToken();
        printf("Token Type: %d, Value: %.*s\n", tok.type, tok.length, tok.value);
    }while(tok.type != TOKEN_EOF && tok.type != TOKEN_INVALID);
}