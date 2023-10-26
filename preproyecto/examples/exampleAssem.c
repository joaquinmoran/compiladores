#include <stdio.h>

int main(int argc, char const *argv[])
{
    int x = 2;
    int y = 2;
    x = x * 2;
    y = y * 2;
    x = (x + x) * x;
    printf("%d", x);
    return 0;
}
