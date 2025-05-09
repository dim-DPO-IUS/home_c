#include<stdio.h>
#include<inttypes.h>

// Ввести два целых числа a и b (a ≤ b) и вывести сумму квадратов всех чисел от a до b.

int main(void)
{
    int8_t a=0,b=0;
    int sum=0;

    scanf("%hhd%hhd", &a, &b);

    for(int i=a; i<=b; i++)
        sum +=i*i;
        
    printf("%d\n", sum);

    return 0;
}