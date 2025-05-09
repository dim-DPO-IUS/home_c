#include<stdio.h>
#include<inttypes.h>

// Ввести целое число и определить, верно ли, что в нём ровно одна цифра «9».

#define N 9

int main(void)
{
    int32_t n=0;
    int8_t num=0, count=0;

    scanf("%d", &n);
    n = n<0?n*-1:n;

    while(n)
    {    
        num = n%10;
        if(num==N) count++;  
        n /=10;
    }

    printf("%s\n", count==1?"YES":"NO");

    return 0;
}