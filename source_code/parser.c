#include "parser.h"
#include "executor.h"
#include <stdio.h>
#include <stdlib.h>


getNextToken getNextTokenFunc;
getTokenData getTokenDataFunc;
getTokenLine getTokenLineCountFunc;
TOKEN_TYPE currentTokenType;

void program(Node *root);
void stmtList(Node *parent);
void stmt(Node *parent);
void declaration(Node *parent);
void funcCall(Node *parent);
void args(Node *parent);
void term(Node *parent);
void literal(Node *parent);
void type(Node *parent);
void expr(Node *parent);

static void parseError(const char *message) {
    fprintf(stderr, "Parse error: %s (current token: %s at line %d)\n", message, tokenTypeToString(currentTokenType), getTokenLineCountFunc());
    exit(EXIT_FAILURE);
}

int accept(TOKEN_TYPE expectedToken){
    if(currentTokenType == expectedToken){
        currentTokenType = getNextTokenFunc();
        return 1;
    }
    return 0;
} 

int expect(TOKEN_TYPE expectedToken){
    if(expectedToken == currentTokenType){
        return 1;
    }
    return 0;
}


void program(Node *root){
    stmtList(root);
}

//stmt_list : stmt+ 
void stmtList(Node *parent){
    Node *node = createNode(STMT_LIST);
    addChild(parent, node);

    while(!expect(TOKEN_EOF)){
        stmt(node);
    }
}

void stmt(Node *parent){
    Node *node = createNode(STMT);
    addChild(parent, node);

    /* stmt : funcCall | declaration */
    if(expect(TOKEN_KW_INT)){
        declaration(node);
    }else if(expect(TOKEN_ID)){
        funcCall(node);
    }else{
        parseError("expected declaration or function call");
    }
}

// Children : type, ID, expr
void declaration(Node *parent){
    Node *node = createNode(DECLARATION);
    addChild(parent, node);

    type(node);

    if(!expect(TOKEN_ID)){
        parseError("expected identifier in declaration");
    }
    Node *idNode = createNode(ID);
    addNodeData(idNode, getTokenDataFunc());
    addNodeLineInfo(idNode, getTokenLineCountFunc());
    addChild(node, idNode);
    accept(TOKEN_ID);

    if(!accept(TOKEN_ASSIGN)){
        parseError("expected '=' in declaration");
    }

    expr(node);

    if(!accept(TOKEN_STMT_END)){
        parseError("expected ';' at end of declaration");
    }
}

void funcCall(Node *parent){

    // ID
    if(!expect(TOKEN_ID)){
        parseError("expected identifier in function call");
    }
    Node *node = createNode(FUNC_CALL);
    addChild(parent, node);
    Node *idNode = createNode(ID);
    addNodeData(idNode, getTokenDataFunc());
    addNodeLineInfo(idNode, getTokenLineCountFunc());
    addChild(node, idNode);
    accept(TOKEN_ID);

    // L_PAREN
    accept(TOKEN_L_PAREN);


    if(!expect(TOKEN_R_PAREN)){
        args(node);
    }

    if(!accept(TOKEN_R_PAREN)){
        parseError("expected ')' in function call");
    }

    if(!accept(TOKEN_STMT_END)){
        parseError("expected ';' at end of function call");
    }
}

void args(Node *parent){
    Node *node = createNode(ARGS);
    addChild(parent, node);
    term(node);
}

void term(Node *parent){
    if(expect(TOKEN_INT_LITERAL)){
        literal(parent);
        return;
    }
    if(expect(TOKEN_ID)){
        Node *node = createNode(VAR);
        addNodeData(node, getTokenDataFunc());
        addNodeLineInfo(node, getTokenLineCountFunc());
        addChild(parent, node);
        accept(TOKEN_ID);
        return;
    }

    parseError("expected term (literal or identifier)");
}

void literal(Node *parent){
    if(!expect(TOKEN_INT_LITERAL)){
        parseError("expected integer literal");
    }
    Node *node = createNode(LITERAL);
    addNodeData(node, getTokenDataFunc());
    addNodeLineInfo(node, getTokenLineCountFunc());
    addChild(parent, node);
    accept(TOKEN_INT_LITERAL);
}

void type(Node *parent){
    if(!expect(TOKEN_KW_INT)){
        parseError("expected type keyword");
    }
    Node *node = createNode(TYPE);
    addNodeData(node, "int");
    addNodeLineInfo(node, getTokenLineCountFunc());
    addChild(parent, node);
    accept(TOKEN_KW_INT);
}

// Doesn't support parse tree updates per token
void expr(Node *parent){
    Node *mainNode = createNode(OP);
    term(mainNode);
    if(expect(TOKEN_ADD_OP)){
        addNodeData(mainNode, "+");
        addNodeLineInfo(mainNode, getTokenLineCountFunc());
        accept(TOKEN_ADD_OP);
        term(mainNode);
    }else{
        addNodeData(mainNode, "=");
        addNodeLineInfo(mainNode, getTokenLineCountFunc());
        addChild(parent, mainNode);
        return;
    }

    while(expect(TOKEN_ADD_OP)){
        Node *newMainNode = createNode(OP);
        addNodeData(newMainNode, "+");
        addNodeLineInfo(newMainNode, getTokenLineCountFunc());
        addChild(newMainNode, mainNode);
        accept(TOKEN_ADD_OP);
        term(newMainNode);
        mainNode = newMainNode;
    }

    Node *assignNode = createNode(OP);
    addNodeData(assignNode, "=");
    addNodeLineInfo(assignNode, getTokenLineCountFunc());
    addChild(assignNode, mainNode);
    addChild(parent, assignNode);
}

Node *initParse(getNextToken getNextTokenFunction, getTokenData getTokenDataFunction, getTokenLine getTokenLineCountFunction) {
    getNextTokenFunc = getNextTokenFunction;
    getTokenDataFunc = getTokenDataFunction;
    getTokenLineCountFunc = getTokenLineCountFunction;

    currentTokenType = getNextTokenFunc();
    Node *root = createNode(PROGRAM);
    return root;
}

void startParse(Node *root) {
    program(root);
}