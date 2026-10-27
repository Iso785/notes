#include <stdio.h>

#define _SIZE1 1000100
#define _SIZE2 110

#define scan(x,size) (scanf("%" #size "s", x) == 1)
#define print(x) ((x)[0] == '\0' ? printf("EMPTY\n") : printf("%s\n", x))

void censour(char* w1, const char* w2){
    int w2_len = 0;
    while (w2[w2_len]) {
        w2_len++;
    }
    if (w2_len == 0) return;
    int dst = 0;
    for (int src = 0; w1[src]; src++) {
        w1[dst] = w1[src];
        dst++;
        if (dst >= w2_len) {
            int check = 1;
            for (int start = 0; start < w2_len; start++) {
                if (w1[dst - w2_len + start] != w2[start]) {
                    check = 0;
                    break;
                }
            }
            if (check) {
                dst -= w2_len;
            }
        }
    }
    w1[dst] = '\0';
}

int main(){
    static char s1[_SIZE1];
    static char s2[_SIZE2];
    if (!scan(s1, 1000000)) return 0;
    if (!scan(s2, 100)) return 0;
    censour(s1, s2);
    print(s1);
    return 0;
}