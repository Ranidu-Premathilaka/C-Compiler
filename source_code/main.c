#include "lexer.h"
#include "parser.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


TOKEN_TYPE getNextTokenType();
char* getTokenValue();

token tokenArray[100];
int currentTokenIndex = 0;
int isInteractiveMode = 0;
Node *parseTree = NULL;

int main(int argc, char *argv[]){

    const char *filename = "test.txt";
    int filenameProvided = 0;

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-i") == 0) {
            isInteractiveMode = 1;
        } else if (!filenameProvided) {
            filename = argv[i];
            filenameProvided = 1;
        }
    }

    FILE *sourceCode = fopen(filename, "rb");
    if (!sourceCode) {
        fprintf(stderr, "Failed to open source file: %s\n", filename);
        return 1;
    }

    initializeLexer(sourceCode);
    parseTree = initParse(getNextTokenType, getTokenValue);
    startParse(parseTree);

    fclose(sourceCode);
    return 0;
}

void displayTokenStream(){
    printf("Token Stream:\n");
    for(int i = 0; i < currentTokenIndex; i++){
        printf("%d: Type: %s, Value: %s\n", i, tokenTypeToString(tokenArray[i].type), tokenArray[i].value);
    }
}

void waitForUser(){
    if(!isInteractiveMode){
        return;
    }
    printf("Press Enter to continue...");
    getchar();
}

TOKEN_TYPE getNextTokenType(){
    system("clear");
    displayTokenStream();
    printf("\nCurrent Abstract Parse Tree:\n");
    displayParseTree(parseTree);
    waitForUser();
    
    tokenArray[currentTokenIndex++] = popCurrentToken();
    return tokenArray[currentTokenIndex-1].type;
}

char* getTokenValue(){
    return tokenArray[currentTokenIndex-1].value;
}