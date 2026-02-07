#include "parseTree.h"
#include "parser.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Node *createNode(int nodeType) {
    Node *node = (Node *)malloc(sizeof(Node));
    node->nodeType = nodeType;

    node->childCapacity = 2;
    node->children = (Node **)malloc(sizeof(Node *) * node->childCapacity);

    node->data = NULL;
    node->childCount = 0;

    return node;
}

void addNodeData(Node *node, const char *data) {
    node->data = (char *)malloc(strlen(data) + 1);
    strcpy(node->data, data);
}

void addChild(Node *parent, Node *child) {
    if (parent->childCount >= parent->childCapacity) {
        parent->childCapacity *= 2;
        parent->children = (Node **)realloc(parent->children, sizeof(Node *) * parent->childCapacity);
    }
    parent->children[parent->childCount] = child;
    parent->childCount++;
}

void freeNode(Node *node) {
    if (node->data) {
        free(node->data);
    }
    for (int i = 0; i < node->childCount; i++) {
        freeNode(node->children[i]);
    }
    free(node->children);
    free(node);
}

static void displayParseTreeHelper(Node *node, int depth) {
    if (!node) return;

    for (int i = 0; i < depth; i++) {
        printf("  ");
    }

    printf("- %s", nodeTypeToString(node->nodeType));
    if (node->data) {
        printf(" data=\"%s\"", node->data);
    }
    printf(" children=%d\n", node->childCount);

    for (int i = 0; i < node->childCount; i++) {
        displayParseTreeHelper(node->children[i], depth + 1);
    }
}

void displayParseTree(Node *node) {
    printf("------------------------------\n");
    displayParseTreeHelper(node, 0);
    printf("------------------------------\n");
}