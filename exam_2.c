#include <stdio.h>
#define SIZE 33

int len(char* str) {
    int len = 0;
    while (str[len]) len++;
    return len;
}

int is_match(char* word1, int start1,char* word2, int len) {
    for (int i = 0; i < len; i++) {
        if (word1[start1 + i] != word2[i]) {
            return 0;
        }
    }
    return 1;
}

void do_task(char* word1,char* word2) {
    int len1 = len(word1);
    int len2 = len(word2);
    
    int maxoverw = (len1 < len2) ? len1 : len2;
    int overw = 0;

    for (int i = maxoverw; i > 0; i--) {
        int start1 = len1 - i; 
        
        if (is_match(word1, start1, word2, i)) {
            overw = i;
            break;
        }
    }
    printf("%s", word1);
    printf("%s\n", word2 + overw);
}



int main() {
    int n;
    char word1[SIZE];
    char word2[SIZE];
    n = scanf("%d",&n);

    for (int i = 0; i < n; i++) {
        scanf("%32s %32s", word1, word2);
        do_task(word1, word2);
    }

    return 0;
}
