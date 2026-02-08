#include "symbolTable.h"
#include <string.h>

Symbol symbolTableArray[100];
int currentSymbolEnd = 0;

SymbolIndex isInSymbolTable(const char *id){
    int i = 0;
    while(i < currentSymbolEnd){
        if(strcmp(id, symbolTableArray[i].symbolName) == 0){
            return i;
        }
        i++;
    }
    return -1;
}

int getSymbolInt(SymbolIndex index){
    return symbolTableArray[index].value.i;
}

int internalCreateSymbol(char *id, SymbolType type, SymbolValue value){
    // Check if already exists
    if(isInSymbolTable(id) != -1) return 0;
    symbolTableArray[currentSymbolEnd].symbolName = strdup(id);
    symbolTableArray[currentSymbolEnd].type = type;
    symbolTableArray[currentSymbolEnd].value = value;
    currentSymbolEnd++;
    return 1;
}

void createIntVarSymbol(char *id, int value){
    SymbolValue x;
    x.i = value;
    internalCreateSymbol(id, SYM_INT_VAR, x);
}