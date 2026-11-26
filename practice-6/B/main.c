#include <stdio.h>

void printer(int open,int close){
    if (open < 0 || close < 0) return;
    if (open == 0 && close == 0) return;
    
    if(open - 1 >= 0){
        printf("(");
        printer(open - 1,close);
    }

    
}

int main(){
    int n = 0;
    scanf("%d", &n);
    printer(n,n);

    return 0;
}