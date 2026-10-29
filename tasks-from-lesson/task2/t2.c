#include <stdio.h>

int main(){
    int a = 5,b = 8;
    int* p;

    p = &a;
    *p *= 3;
    p = &b;
    *p += a;

    printf("a=%d b = %d\n",a,b);
}