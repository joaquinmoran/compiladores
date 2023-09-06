#ifndef AST_h
#define AST_h


struct treeNode{
    char *type;
    char *name;
    int value;
};

struct tree{
    struct tree *left;
    struct tree *right;
    struct treeNode info;
};

struct tree *newTree(struct treeNode info, struct tree *leftChild, struct tree *rightChild);
struct tree *newNode(char *type, char *name, int value);
void printNode(struct tree *tree);

#endif