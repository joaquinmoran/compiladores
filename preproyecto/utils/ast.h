#ifndef AST_h
#define AST_h


struct treeNode{
    char *exprType;
    char *type;
    char *name;
    int value;
};

struct tree{
    struct tree *left;
    struct tree *right;
    struct treeNode info;
};

extern struct tree *ast;

struct tree *newTree(struct treeNode info, struct tree *leftChild, struct tree *rightChild);
struct tree *newNode(char *eType, char *type, char *name, int value);
void inOrderPrint(struct tree *root);

#endif