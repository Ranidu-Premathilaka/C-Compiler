#include "lexer.h"
#include "lexerDFA.h"

token computeNextTokenFromSource();
token createToken(TOKEN_TYPE type, const char* start, int length);
int skipChars(char ch);
char peakCurrentChar();
void popCurrentChar();

token currentToken;
token lookaheadToken;
reader lexerReader;


void initializeLexer(FILE *sourceCode){
    lexerReader.sourcePointer = sourceCode;

    //initialize current and lookahead characters
    popCurrentChar(); //load first character

    currentToken = computeNextTokenFromSource();
    lookaheadToken.type = TOKEN_INVALID;
}

token popCurrentToken(){
    token tempToken = currentToken;
    if(lookaheadToken.type == TOKEN_INVALID){
        currentToken = computeNextTokenFromSource();
    }else{
        currentToken = lookaheadToken;
        lookaheadToken.type = TOKEN_INVALID;
    }

    return tempToken;
}

token lookaheadNextToken(){
    if(lookaheadToken.type != TOKEN_INVALID){
        return lookaheadToken;
    }
    lookaheadToken = computeNextTokenFromSource();
    return lookaheadToken;

}

token computeNextTokenFromSource(){

    STATE currentState = START_I;
    STATE nextState = TRAP_STATE;
    int currentLexemeLength = 0;
    char keywordBuffer[MAX_LEXEME_LENGTH];

    while(1){

        if(skipChars(peakCurrentChar())){
            if(currentLexemeLength){
                break;
            }else{
                popCurrentChar();
                continue;
            }
        }
        
         nextState = getNextState(currentState, peakCurrentChar());
         if(nextState == TRAP_STATE){
            break;
         }

        keywordBuffer[currentLexemeLength++] = peakCurrentChar();
        currentState = nextState;
        popCurrentChar();
    }

    if(isFinalState(currentState)){
        TOKEN_TYPE tokenType = getTokenTypeForFinalState(currentState);
        return createToken(tokenType, keywordBuffer, currentLexemeLength);
    }else{

        // Handle invalid token
        return createToken(TOKEN_INVALID, keywordBuffer, currentLexemeLength);
    }

}

token createToken(TOKEN_TYPE type, const char* start, int length){
    token tok;
    tok.type = type;
    tok.value = (char*) malloc((length + 1) * sizeof(char));
    for(int i = 0; i < length; i++){
        ((char*)tok.value)[i] = start[i];
    }
    ((char*)tok.value)[length] = '\0';

    return tok;
}

int skipChars(char ch){
    return ch == ' ' || ch == '\n' || ch == '\t' || ch == '\r';
}

char peakCurrentChar(){
    return lexerReader.currentChar;
}

void popCurrentChar(){
    int c = fgetc(lexerReader.sourcePointer);

    if(c != EOF){
        lexerReader.currentChar = (char)c;
    }else{
        lexerReader.currentChar = '\0';
    }
}
