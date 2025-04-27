#include <stdio.h>

int main(void){
    int a=0, b=0, c=0; 
    int sum=0;

    scanf("%d%d%d", &a, &b, &c);
    
    sum = a + b + c;

    printf("%d+%d+%d=%d\n", a,b,c,sum);

    return 0;
}