#ifndef AST_h
#define AST_h


struct treeNode{
    char *type;
    char *name;
    int value;
};

struct tree{
    tree *left;
    tree *right;
    treeNode info;
};

struct tree *newTree(struct treeNode info, struct tree *leftChild, struct tree *rightChild);

#endif