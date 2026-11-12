#include <stdio.h>

double f(double a,double x){
    double b = (x*x*x) + (a * x); 
    return b;
}

int main(){
    double a,b;
    scanf("%lf %lf", &a, &b);

    double l = -1000;
    double r = 1000;
    double m = 0;

    for (int i = 0;i < 100;i++){
        m = (l + r) / 2;
        if (f(a,m) < b) l = m;
        else r = m;
    }

    printf("%.6f\n",m);

    return 0;
}