#include <stdio.h>

void swap_disk(int Branch[3][16],int from,int to){
    int disk = 0;

    for (int i = 15;i >= 0;i--){
        if (Branch[from][i] != 0){
            disk = Branch[from][i];
            Branch[from][i] = 0;
            break;
        }
    }

    for (int i = 0;i < 16;i++){
        if (Branch[to][i] == 0){
            Branch[to][i] = disk;
            break;
        }
    }

    printf("%c -> %c\n", from + 65, (to + 65));
}

void hanoi(int Branch[3][16],int from,int none,int to,int size){
    if (size == 0) return;

    hanoi(Branch,from,to,none,size - 1);
    swap_disk(Branch,from,to);
    hanoi(Branch,none,from,to,size - 1);
}

int main(){
    int A [3][16] = {0};
    int n = 0;
    scanf("%d", &n);
    for (int i = 0; i < n;i++){
        A[0][i] = n - i;
    }
    hanoi(A,0,1,2,n);
    return 0;
}