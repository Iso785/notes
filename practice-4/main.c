#include <stdio.h>

int main(){
    FILE* infile = fopen("input.txt","r");
    FILE* outfile = fopen("output.txt","w");
    
    if (infile == NULL) return 1;
    if (outfile == NULL) return 1;

    int inc = 0;
    int state = 0;

    
    while ((inc = getc(infile)) != EOF) {
        switch (state) {
            case 0:
                if (inc == '/') {
                    state = 1;
                } else if (inc == '"') {
                    putc(inc, outfile);
                    state = 5;
                } else if (inc == '\'') {
                    putc(inc, outfile);
                    state = 7;
                } else {
                    putc(inc, outfile);
                }
                break;

            case 1:
                if (inc == '/') {
                    state = 2;
                } else if (inc == '*') {
                    state = 3;
                } else {
                    putc('/', outfile);
                    if (inc == '"') {
                        putc(inc, outfile);
                        state = 5;
                    } else if (inc == '\'') {
                        putc(inc, outfile);
                        state = 7;
                    } else {
                        putc(inc, outfile);
                        state = 0;
                    }
                }
                break;

            case 2:
                if (inc == '\n') {
                    putc(inc, outfile);
                    state = 0;
                }
                break;

            case 3:
                if (inc == '*') {
                    state = 4;
                }
                break;

            case 4:
                if (inc == '/') {
                    putc(' ', outfile);
                    state = 0;
                } else if (inc != '*') {
                    state = 3;
                }
                break;

            case 5:
                putc(inc, outfile);
                if (inc == '\\') {
                    state = 6;
                } else if (inc == '"') {
                    state = 0;
                }
                break;

            case 6:
                putc(inc, outfile);
                state = 5;
                break;

            case 7:
                putc(inc, outfile);
                if (inc == '\\') {
                    state = 8;
                } else if (inc == '\'') {
                    state = 0;
                }
                break;

            case 8:
                putc(inc, outfile);
                state = 7;
                break;
        }
    }
    
    if (state == 1) {
        putc('/', outfile);
    }

    fclose(infile);
    fclose(outfile);

    // scanf("%d", &outc);
    // remove("output.c");
    // remove("main");

    return 0;
}