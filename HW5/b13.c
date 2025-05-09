#include<stdio.h>
#include<inttypes.h>

// Посчитать количество четных и нечетных цифр числа.
// Формат входных данных: Одно целое неотрицательное число.

int main(void)
{
    uint32_t n=0;
    uint8_t even=0, uneven=0;

    scanf("%u", &n);

    while(n)
    {
        n%2==0?even++:uneven++;
        n /=10;
    }

    printf("%hhu %hhu\n", even,uneven);

    return 0;
}