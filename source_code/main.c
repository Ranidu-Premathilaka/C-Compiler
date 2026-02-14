#include "lexer.h"
#include "parser.h"
#include "executor.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


TOKEN_TYPE getNextTokenType();
char* getTokenValue();
int getTokenLineCount();
void handleArgs(int argc, char *argv[]);

token tokenArray[100];
int currentTokenIndex = 0;

int isInteractiveMode = 0;
int delayBetweenTokenReads = 0; // milliseconds
const char *filename = "";

Node *parseTree = NULL;

int main(int argc, char *argv[]){

    handleArgs(argc, argv);

    FILE *sourceCode = fopen(filename, "rb");
    if (!sourceCode) {
        printf("Error: Could not open source file '%s'.\n", filename);
        return 1;
    }

    initializeLexer(sourceCode);
    parseTree = initParse(getNextTokenType, getTokenValue, getTokenLineCount);
    startParse(parseTree);

    printf("\nExecuting Program:\n");
    traverseAndExecute(parseTree);

    fclose(sourceCode);
    return 0;
}

void handleArgs(int argc, char *argv[]){
    for(int i = 1; i < argc; i++){
        switch(argv[i][1]){
            case 'i':
                isInteractiveMode = 1;
                break;
            case 'd':
                if(i + 1 < argc && !isInteractiveMode){
                    delayBetweenTokenReads = atoi(argv[++i]);
                }
                break;
        }
    }

    if(argc < 2){
        printf("Usage: ./a.out <source_file> [-i] [-d delay_ms] \n");
        exit(EXIT_FAILURE);
    }

    filename = argv[1];
}

void displayTokenStream(){
    printf("Token Stream:\n");
    for(int i = 0; i < currentTokenIndex; i++){
        printf("%d: Type: %s, Value: %s\n", i, tokenTypeToString(tokenArray[i].type), tokenArray[i].value);
    }
}

void waitForUser(){
    if(!isInteractiveMode){
        usleep(delayBetweenTokenReads * 1000);
        return;
    }
    printf("Press Enter to continue...\n");
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

int getTokenLineCount(){
    return tokenArray[currentTokenIndex-1].lineNumber;
}