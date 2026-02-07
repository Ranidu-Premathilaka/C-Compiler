#ifndef PARSE_TREE_H
#define PARSE_TREE_H

typedef struct Node {
    int nodeType; // e.g. PROGRAM, STMT_LIST, EXPR, ...
    struct Node **children;
    char *data;
    int childCount;
    int childCapacity;
} Node;


Node *createNode(int nodeType);
void addNodeData(Node *node, const char *data);
void addChild(Node *parent, Node *child);
void freeNode(Node *node);
void displayParseTree(Node *node);

#endif