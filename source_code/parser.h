#include "tokenType.h"
#include "parseTree.h"
#include "symbolTable.h"

#ifndef PARSER_H
#define PARSER_H

typedef TOKEN_TYPE (*getNextToken)();
typedef char* (*getTokenData)();
typedef int (*getTokenLine)();

typedef enum {
    PROGRAM,
    STMT_LIST,
    STMT,
    DECLARATION,
    FUNC_CALL,
    ARGS,
    TERM,
    LITERAL,
    VAR,
    TYPE,
    EXPR,
    ID,
    OP
} NodeType;

static const char *nodeTypeToString(int nodeType) {
    switch (nodeType) {
        case PROGRAM:     return "PROGRAM";
        case STMT_LIST:   return "STMT_LIST";
        case STMT:        return "STMT";
        case DECLARATION: return "DECLARATION";
        case FUNC_CALL:   return "FUNC_CALL";
        case ARGS:        return "ARGS";
        case TERM:        return "TERM";
        case LITERAL:     return "LITERAL";
        case VAR:         return "VAR";
        case TYPE:        return "TYPE";
        case EXPR:        return "EXPR";
        case ID:          return "ID";
        case OP:          return "OP";
        default:          return "UNKNOWN";
    }
}




Node *initParse(getNextToken getNextTokenFunction, getTokenData getTokenDataFunction, getTokenLine getTokenLineCountFunction);
void startParse(Node *root);

#endif