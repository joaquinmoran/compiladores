#ifndef SYMTABLE_h
#define SYMTABLE_h
#include <stdbool.h>

struct nodeInfo{
    char *name;
    char *flag;
    char *type;
    char *param;
    int value;
    int offset;
};

struct node{
    struct node *next;
    struct nodeInfo info;
};

void initialize_list();
void addNodeToTable(struct node *newNode);
void printTable();
bool setValueByName(int value, char *name);
int getValueByName(char *name);
struct node *getNodeByName(char *name);
struct node *newTableNode(char *n, char *f, char *t, char *p, int v);



#endif