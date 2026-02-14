#include "tokenType.h"

#ifndef LEXER_H
#define LEXER_H

#include <stdio.h>
#include <stdlib.h>

#define MAX_LEXEME_LENGTH 256

typedef struct{
    TOKEN_TYPE type;
    char* value;
    int lineNumber;
} token;

typedef struct{
    FILE *sourcePointer;
    char currentChar;
} reader;

token popCurrentToken();
token lookaheadNextToken();
void initializeLexer(FILE *sourceCode);

#endif