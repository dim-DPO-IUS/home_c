#include <stdio.h>

int main(void){
    int a=0, b=0, c=0; 

    scanf("%d%d%d", &a, &b, &c);

    printf("%.2f\n", (a+b+c)/3.0);

    return 0;
}