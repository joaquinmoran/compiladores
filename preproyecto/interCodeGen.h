#ifndef INTERCODEGEN_h
#define INTERCODEGEN_h

#include "ast.h"

struct listNode{
    struct treeNode *left;
    struct treeNode *right;
    struct treeNode *info;
    struct listNode *next;
    char *instr;
};


void breadthFirstTraversal(struct tree *root);

#endif