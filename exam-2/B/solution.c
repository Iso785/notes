#include <stdio.h>
#define SIZE 100001
#define scan_m(x,n) for(int i = 0;i < n;i++) scanf("%lld", &x[i])
#define print_m(x) for(int i = 0;i < n;i++) printf("%lld ", x[i])  
typedef struct
{
    int l;
    int r;
}input;
#define scan_in(x) scanf("%d %d",&x.l,&x.r)

void reverse (long long *l,long long *r){
    while (l < r)
    {
        long long tmp = *l;
        *l = *r;
        *r = tmp;

        l++;
        r--;
    }
    
}

int main(){
    long long values[SIZE] = {0};
    int q = 0;
    int n = 0;
    input qs = {0};

    scanf("%d %d", &n, &q);
    scan_m(values,n);
    for(;q > 0;--q) {
        scan_in(qs);
        reverse(values + qs.l - 1,values + qs.r - 1);
    }
    print_m(values);
    return 0;
}