#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

typedef enum{
    SYM_INT_VAR,
    SYM_FUNC,
}SymbolType;

typedef union{
    int i;
}SymbolValue;

typedef int SymbolIndex;

typedef struct{
    char *symbolName;
    SymbolType type;
    SymbolValue value;
}Symbol;


int isInSymbolTable(const char *id);
int getSymbolInt(SymbolIndex index);
void createIntVarSymbol(char *id, int value);


#endif