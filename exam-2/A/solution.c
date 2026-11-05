#include <stdio.h>
#define SIZE 100001

typedef struct
{
    int min;
    int min_id;
    int max;
    int max_id;
}mnmx;

mnmx search(long long *values,int n){
    mnmx def = {0};
    def.max = values[0];
    def.min = values[0];
    for (int i = 0;i < n;i++){
        if (def.max < values[i]){
            def.max = values[i];
            def.max_id = i;
        }

        if (def.min > values[i]){
            def.min = values[i];
            def.min_id = i;
        }
    }
    return def;
}

void swap(long long *values, mnmx def){
    int tmp = values[def.min_id];
    values[def.min_id] = values[def.max_id];
    values[def.max_id] = tmp;
}

int main(){
    long long values[SIZE] = {0};
    int n = 0;
    scanf ("%d", &n);
    for(int i = 0;i < n;i++){
        scanf("%lld",&values[i]);
    }

    swap(values,search(values,n));
    for(int i = 0;i < n;i++){
        printf("%lld ",values[i]);
    }

    return 0;
}