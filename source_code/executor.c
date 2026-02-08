#include "executor.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Forward declarations for internal helpers
void execute(Node *node);
void executeDeclaration(Node *node);
void executeFuncCall(Node *node);
int eval(Node *node);
int evalVar(Node *node);
int evalOp(Node *node);

void traverseAndExecute(Node *node) {
    if (!node) return;

    for (int i = 0; i < node->childCount; i++) {
        traverseAndExecute(getChild(node, i));
    }

    execute(node);
}

void execute(Node *node){
    if (!node) return;

    switch(node->nodeType){
        case DECLARATION:
            executeDeclaration(node);
            break;
        case FUNC_CALL:
            executeFuncCall(node);
            break;
        default:
            break;
    }
}

void executeDeclaration(Node *node){
    if (getChildCount(node) < 3){return;}

    // [0] = TYPE, [1] = ID, [2] = OP
    Node *idNode = getChild(node, 1);
    if(idNode->nodeType != ID || !getNodeData(idNode)){
        printf("Runtime error: invalid declaration, expected identifier.\n");
        exit(EXIT_FAILURE);
    }

    Node *exprNode = getChild(node, 2);
    if(exprNode->nodeType != OP || !getNodeData(exprNode) || strcmp(getNodeData(exprNode), "=") != 0){
        printf("Runtime error: invalid declaration, expected '=' operator.\n");
        exit(EXIT_FAILURE);
    }

    int value = eval(exprNode);

    if (isInSymbolTable(getNodeData(idNode)) == -1) {
        createIntVarSymbol(getNodeData(idNode), value);
    } else {
        fprintf(stderr, "variable '%s' already defined\n", getNodeData(idNode));
        exit(EXIT_FAILURE);
    }
}

void executeFuncCall(Node *node){
    if (getChildCount(node) < 1){return;}

    // [0] = ID
    Node *idNode = getChild(node, 0);
    if (!idNode || !getNodeData(idNode) || idNode->nodeType != ID) {
        printf("Runtime error: invalid function call, expected identifier.\n");
        exit(EXIT_FAILURE);
    }

    // the print function is supported by default
    if (strcmp(getNodeData(idNode), "print") == 0) {

        Node *argsNode = getChild(node, 1);
        if (!argsNode || getChildCount(argsNode) != 1) {
            printf("Runtime error: print expects one argument.\n");
            exit(EXIT_FAILURE);
        }

        // currently print only supports one argument
        Node *argExpr = getChild(argsNode, 0);
        int value = eval(argExpr);
        printf("%d\n", value);
    } else {
        fprintf(stderr, "Runtime error: unknown function '%s'.\n", idNode->data);
    }
}

int eval(Node *node){
    if (!node) return 0;

    switch(node->nodeType){
        case LITERAL:
            if (!getNodeData(node)) return 0;
            return atoi(node->data);

        case VAR: 
            return evalVar(node);

        case OP:
            return evalOp(node);

        default:
            printf("Runtime error: cannot evaluate node of type '%d'.\n", node->nodeType);
            exit(EXIT_FAILURE);        
    }
}

int evalVar(Node *node){
    int index = isInSymbolTable(node->data);
    if (index == -1) {
        printf("Runtime error: undefined variable '%s'.\n", node->data);
        exit(EXIT_FAILURE);
    }
    return getSymbolInt(index);
}

int evalOp(Node *node){

    if (strcmp(getNodeData(node), "+") == 0) {
        if(getChildCount(node) != 2){
            printf("Runtime error: '+' operator expects two operands.\n");
            exit(EXIT_FAILURE);
        }
        int left = eval(getChild(node, 0));
        int right = eval(getChild(node, 1));
        return left + right;
    }

    if (strcmp(getNodeData(node), "=") == 0) {
        if(getChildCount(node) != 1){
            printf("Runtime error: '=' operator expects only one operand.\n");
            exit(EXIT_FAILURE);
        }
        return eval(getChild(node, 0));
    }

    // Unknown operator
    printf("Runtime error: unknown operator '%s'.\n", getNodeData(node));
    exit(EXIT_FAILURE);
}