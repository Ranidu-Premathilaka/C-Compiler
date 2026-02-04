#include "tokens.h"

token currentToken;
token lookaheadToken;
char* sourcePointer;

void initializeLexer(const char* sourceCode){

}

token popNextToken(){
    return currentToken;
}

token lookaheadNextToken(){
    if(lookaheadToken.type != TOKEN_INVALID){
        return lookaheadToken;
    }

}

token computeNextTokenFromSource(){

    while(*sourcePointer != '\0'){
        if(skipChars(*sourcePointer)){
            sourcePointer++;
            continue;
        }

        if(*sourcePointer == ';'){
            token tok = createToken(TOKEN_STMT_END, sourcePointer, 1);
            sourcePointer++;
            return tok;
        }

        


        sourcePointer++;
    }

}

token createToken(TOKEN_TYPE type, const char* start, int length){
    token tok;
    tok.type = type;
    tok.value = start;
    tok.length = length;
    return tok;
}

int skipChars(char ch){
    return ch == ' ' || ch == '\n' || ch == '\t' || ch == '\r';
}