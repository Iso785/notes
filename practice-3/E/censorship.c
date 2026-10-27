#include <stdio.h>

#define _SIZE1 1000100
#define _SIZE2 110

#define scan(x,size) scanf("%" #size "s",x)
#define print(x) (x[0] == '\0') ? printf("EMPTY") : printf("%s\n",x)

void censour(char* w1,const char* w2){
    for(int i = 0,check = 1,start = 0; w1[i];i++,check = 1,start = 0){
        if (w1[i] == w2[start]){
            for(start;w2[start];start++){
                if(w1[start + i] != w2[start]) {
                    check = 0;
                    break;
                }   
            }
            if (check){
                for(int w = 0,count = i;w < start;w++,count = i){
                    while (w1[count]) {
                        w1[count] = w1[count + 1];
                        count++;
                    }
                }
                i = -1;
            }
        }
    }
}

int main(){
    char s1[_SIZE1] = {"\0"},s2[_SIZE2] = {'\0'};
    scan(s1,1000000);
    scan(s2,100);
    censour(s1,s2);
    print(s1);
    return 0;
}