#include <stdio.h>
#include <math.h>

typedef struct
{
    double x;
    double y;
}position;

#define scanpos(pos) scanf("%lf %lf",&pos.x,&pos.y);
#define lenpos(pos) (sqrt((double)((pos.x*pos.x)+(pos.y*pos.y))))

int main(){
    position a[101] = {0};
    position start = {0};

    int n = 0;
    int indx = 0;
    double min = 0;

    scanpos(start);
    scanf("%d",&n);

    double control = lenpos(start);
    for (int i = 0;i < n;i++) {
        scanpos(a[i]);
        min = lenpos(a[i]);
        if (min > control)indx = i;
    }

    printf("%d %.4f",indx + 1, (lenpos(a[indx])));
    return 0;
}
