#include <stdio.h>

void reverse(int* arr,int n){
    int* start = arr;
    int* end = arr + (n - 1);

    while (start < end)
    {
        int tmp = *start;
        *start = *end;
        *end = tmp;

        end--;
        start++;
    }
}

int main(){
    int arr[] = {1,2,3,4,5,6,7};
    int n = 7;
    reverse(arr,n);

    for(int i = 0;i < 7;i++) printf("%d," ,arr[i]);
    return 0;
}