#include <stdio.h>

int strle(const char* a){
    int count = 0;
    while (*a++) count++;
    return count;
}

int main(){
    FILE* input = fopen("input.txt","r");
    FILE* output = fopen("output.txt","w");

    if (input != NULL && output != NULL){
        char stars[8] = {'\0'};

        int bounty = 0;
        int ch = 0;
        int sum = 0;

        while (fscanf(input, "%s %d", stars, &bounty) == 2)
        {
            if (strle(stars) == 5) sum += bounty;
        }
        fprintf(output,"%d", sum);

        fclose(output);
        fclose(input);
    }else perror("one of files is Null");
    return 0;
}