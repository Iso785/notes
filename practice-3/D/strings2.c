#include <stdio.h>

/*
NOTE
char a -  97 ASCI
char z - 122 ASCI
*/

#define ms 200010
#define as 26
#define sc 'a'

#define scan(b) scanf("%200000s", b)
#define min(a, b) ((a) < (b) ? (a) : (b))
#define c2i(c) ((int)(c) - sc)

typedef struct {
    char text[ms];
    int len;
    int u_tot;
} str_t;

typedef struct {
    int cnt[as];
    int u_now;
} win_t;

void anz(str_t *s) {
    int vis[as] = {0};
    s->len = 0;
    s->u_tot = 0;
    while (s->text[s->len] != '\0') {
        int i = c2i(s->text[s->len]);
        if (!vis[i]) {
            vis[i] = 1;
            s->u_tot++;
        }
        s->len++;
    }
}

void w_add(win_t *w, char c) {
    int i = c2i(c);
    if (w->cnt[i] == 0) {
        w->u_now++;
    }
    w->cnt[i]++;
}

void w_rm(win_t *w, char c) {
    int i = c2i(c);
    w->cnt[i]--;
    if (w->cnt[i] == 0) {
        w->u_now--;
    }
}

int do_task(const str_t *s) {
    win_t w = {0};
    int l = 0, r = 0;
    int ans = s->len + 1;

    for (r = 0; r < s->len; r++) {
        w_add(&w, s->text[r]);
        while (w.u_now == s->u_tot) {
            ans = min(ans, r - l + 1);
            w_rm(&w, s->text[l]);
            l++;
        }
    }
    return ans;
}

int main() {
    static str_t s = {0};
    scan(s.text);
    anz(&s);
    printf("%d\n", do_task(&s));
    return 0;
}
