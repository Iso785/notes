#include <stdio.h>
#define SIZE 10000

int max_m(int* a,int size){
	int m = a[0];int count = 0;
	for (int i = 0;i < size;i++) if (m < a[i]) m = a[i];
    for (int i = 0;i < size;i++) if (a[i] < m) count++;
	return count;
}

unsigned long long A(unsigned long long m,unsigned long long n){
    if (m == 0) return n + 1;
    else if (m > 0 && n == 0) return A(m - 1,1);
    else if (m > 0 && n > 0) return A(m - 1, A(m, n - 1));
}

int main(){
	int a[SIZE] = {0};
	int count = 0;int n  = 0 ;
    scanf("%d",&n);
	for (int i = 0;i < n;i++) scanf("%d",&a[i]);
	count = max_m(a,n);

    printf("%d\n",count);

    printf("%lld",A(4ULL,0ULL));
    return 0;
}
