#include "tokenType.h"
#include "parseTree.h"

#ifndef PARSER_H
#define PARSER_H

typedef TOKEN_TYPE (*getNextToken)();
typedef char* (*getTokenData)();

typedef enum {
    PROGRAM,
    STMT_LIST,
    STMT,
    DECLARATION,
    FUNC_CALL,
    ARGS,
    TERM,
    LITERAL,
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
        case TYPE:        return "TYPE";
        case EXPR:        return "EXPR";
        case ID:          return "ID";
        case OP:          return "OP";
        default:          return "UNKNOWN";
    }
}




Node *initParse(getNextToken getNextTokenFunction, getTokenData getTokenDataFunction);
void startParse(Node *root);

#endif