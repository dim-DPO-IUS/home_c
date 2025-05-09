#include<stdio.h>
#include<inttypes.h>

// Организовать ввод натурального числа с клавиатуры. Программа должна определить наименьшую и наибольшую цифры, которые входят в состав данного натурального числа.
// Формат входных данных: Целое неотрицательное число

int main(void)
{
    uint64_t n=0;
    scanf("%lu", &n);
    
    uint8_t num=0, min=n%10, max=0;

    while(n)
    {
        num = n%10;
        max = num>max?num:max;
        min = num<min?num:min;
        n /=10;
    }

    printf("%u %u\n", min,max);

    return 0;
}