#include <stdio.h>

void printInt(int x){
    printf("%d\n",x);
}

void printBool(int x){
    if(x != 0){
        printf("True\n");
    }else{
        printf("False\n");
    }
}