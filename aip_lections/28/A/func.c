#include <stdio.h>
#define SIZE 100000

int get_len(unsigned long long value){
    int len = 0;
    do{
        len++;
        value /= 10;
    } while (value > 0);
    
    return len;
}

int function(unsigned long long value,const int k){
    if (k < 0) return -1;
    int len = get_len(value);
    for (int i = 0;i < len - 1 - k;i++) value /= 10;
    return value % 10;
}

int main(){
    unsigned long long value = 12345678910111213ULL;
    int k = 0;
    scanf("%d", &k);


    //необязательный код!!!
    printf("%llu - исходное число\n%*c\n %d <- значение на месте %d индекса (введенного значения k)"
        ,value,k + 1,'^',function(value,k),k);

    return 0;
}