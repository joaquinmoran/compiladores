#include <stdio.h>

void printInt(int x){
    printf("RESULT: %d\n",x);
}

void printBool(int x){
    if(x != 0){
        printf("RESULT: True\n");
    }else{
        printf("RESULT: False\n");
    }
}