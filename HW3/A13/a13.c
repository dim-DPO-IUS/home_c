#include <stdio.h>

int main(void){
    int a=0; 
    short sum=0;

    scanf("%d", &a);

    sum = (a/100) * (a%100/10) * (a%10);

    printf("%d\n", sum);

    return 0;
}