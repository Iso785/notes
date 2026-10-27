#include <stdio.h>

/*
NOTE
char a -  97 ASCI
char z - 122 ASCI
*/

#define SIZE 200010
#define ASCI 97
typedef struct {
    char text[SIZE];
    int len;
    int cnt[26];
    int nlen;
} string;

#define scan_s(a) scanf("%200000s", a.text);
#define print_s(a) printf("%s\nSize: %d\nContains: %d",a.text, a.len, a.nlen);

int check(string *word){
    int len = 0;
    for(int i = 0;i < 26;i++) len += word->cnt[i];
    return len;
}

int main(){
    static string word = {0};
    int currlen = 0,explen = 0;
    char *l = word.text;
    char *r = word.text;

    scan_s(word);

    for(;word.text[word.len];word.len++);
    for(int i = 0;i < word.len;i++) word.cnt[(int)word.text[i] - ASCI] = 1;
    for(int i = 0;i < 26;i++) word.nlen += word.cnt[i];
    for(int i = 0;i < word.len;i++) word.cnt[i] = 0;

    while(*r){
        if (check(&word) < word.nlen){
            r++;
        }
    }

    print_s(word);
    return 0;
}