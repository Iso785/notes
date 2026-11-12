#include <stdio.h>

#define SIZE 26
#define u2l(x) (((x) >= 'A' && (x) <= 'Z') ? (char)((x) + 32) : (x))
#define c2ind(x) ((x) - 'a')

typedef struct
{
    int max;
    int indx;
}fuldat;


fuldat max(const int* chars){
    fuldat data = {chars[0],0};
    for(int i = 0;i < SIZE;i++) data = (chars[i] > data.max) ? (fuldat){chars[i],i} : (fuldat){data.max,data.indx};
    return data;
}

int main(){
    int chars[SIZE] = {0};
    int c;
    FILE* fp = fopen("files/data.txt","r");
    if(fp)
    {
        while((c=getc(fp))!= EOF)
        {
            int lower = u2l(c);
            int indx = c2ind(lower);
            if (indx >= 0 && indx < SIZE){
                chars[indx]++;
            }
        }
        fclose(fp);
    }

    for(int i = 0;i < SIZE;i++) printf("%-2d %-2d %c\n",i + 1,chars[i],i + 'a');
    printf("max -> %c, %d times",max(chars).indx + 'a', max(chars).max);
    
    return 0;
}