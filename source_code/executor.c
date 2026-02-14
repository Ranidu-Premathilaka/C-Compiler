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

// Centralized error handler for nodes
void runtimeError(Node *node, const char *errorText) {
    printf("Runtime error: %s\n", errorText);
    if (node) {
        if (node->data) {
            printf("  Node data: %s\n", node->data);
        }
        if(node->lineNumber) {
            printf("  Line number: %d\n", node->lineNumber);
        }
    }
    exit(EXIT_FAILURE);
}

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
        runtimeError(idNode, "invalid declaration, expected identifier.");
    }

    Node *exprNode = getChild(node, 2);
    if(exprNode->nodeType != OP || !getNodeData(exprNode) || strcmp(getNodeData(exprNode), "=") != 0){
        runtimeError(exprNode, "invalid declaration, expected '=' operator.");
    }

    int value = eval(exprNode);

    if (isInSymbolTable(getNodeData(idNode)) == -1) {
        createIntVarSymbol(getNodeData(idNode), value);
    } else {
        runtimeError(idNode, "variable already defined");
    }
}

void executeFuncCall(Node *node){
    if (getChildCount(node) < 1){return;}

    // [0] = ID
    Node *idNode = getChild(node, 0);
    if (!idNode || !getNodeData(idNode) || idNode->nodeType != ID) {
        runtimeError(idNode, "invalid function call, expected identifier.");
    }

    // the print function is supported by default
    if (strcmp(getNodeData(idNode), "print") == 0) {

        Node *argsNode = getChild(node, 1);
        if (!argsNode || getChildCount(argsNode) != 1) {
            runtimeError(argsNode, "print expects one argument.");
        }

        // currently print only supports one argument
        Node *argExpr = getChild(argsNode, 0);
        int value = eval(argExpr);
        printf("%d\n", value);
    } else {
        runtimeError(idNode, "unknown function");
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
            runtimeError(node, "cannot evaluate node of this type.");
            return -1; // Unreachable
    }
}

int evalVar(Node *node){
    int index = isInSymbolTable(node->data);
    if (index == -1) {
        runtimeError(node, "undefined variable");
    }
    return getSymbolInt(index);
}

int evalOp(Node *node){

    if (strcmp(getNodeData(node), "+") == 0) {
        if(getChildCount(node) != 2){
            runtimeError(node, "'+' operator expects two operands.");
        }
        int left = eval(getChild(node, 0));
        int right = eval(getChild(node, 1));
        return left + right;
    }

    if (strcmp(getNodeData(node), "=") == 0) {
        if(getChildCount(node) != 1){
            runtimeError(node, "'=' operator expects only one operand.");
        }
        return eval(getChild(node, 0));
    }

    // Unknown operator
    runtimeError(node, "unknown operator");
    return -1; 
}