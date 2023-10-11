#ifndef INTERCODEGEN_h
#define INTERCODEGEN_h

struct listNode{
    struct listNode *next;
    char *instr;
};


void breadthFirstTraversal(struct tree *root);

#endif