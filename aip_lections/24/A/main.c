#include <stdio.h>

unsigned recursion(unsigned n){
    if (n == 1) return 1;
    return recursion(n - 1) + 2 * (n - 1) + 1;
}

int main(){
    unsigned n = 0U;
    scanf("%u", &n);
    printf("квадрат числа %u = %u",n,recursion(n));
    return 0; 
}