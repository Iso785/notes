#include <stdio.h>

#define Size 33
#define MIN(x,y) ((x < y) ? x : y)
#define scan(x) _Generic((x),\
    int: scanf("%d", &x),\
    char: scanf("%c",&x)\
)
#define FOR(x) for(int i = 0;i < x;i++)
#define MATRIX(type,x) type x[Size]

typedef struct 
{
  MATRIX(char,chars);
  int len;
} matrix;


void addwithcut(){
        int start = 0;
        matrix s1,s2;
        scanf("%32s %32s", s1.chars, s2.chars);

        for (;s1.chars[s1.len] && s1.len < Size; s1.len++);
        for (;s2.chars[s2.len] && s2.len < Size; s2.len++);

        for(int i = 1, match = 1; i <= MIN(s1.len,s2.len);i++,match = 1){
            for (int k = 0; k < i;k++ ){
                if (s2.chars[k] != s1.chars[s1.len - i + k]){
                    match--;
                    break;
                }
            }
            if (match) start = i;
        }

        printf("%s",s1.chars);
        printf("%s\n",s2.chars + start);
}

int main(){
    int n = 0;
    scan(n);
    FOR(n) addwithcut();
    return 0;
}