#include<stdio.h>
#include<inttypes.h>

// Ввести целое число и определить, верно ли, что в его записи есть две одинаковые цифры, стоящие рядом.

int main(void)
{
    int32_t n=0;

    scanf("%d", &n);
    n = n<0?n*-1:n;

    int8_t result=0, num2=0, num1=n%10;

    while(n>=10)
    {    
        n /=10;
        num2 = n%10;
        if (result = num1==num2)
            break;
        num1 = num2;
    }

    printf("%s\n", result?"YES":"NO");

    return 0;
}