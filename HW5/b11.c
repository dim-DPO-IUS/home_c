#include<stdio.h>
#include<inttypes.h>

// Ввести целое число и «перевернуть» его, так чтобы первая цифра стала последней и т.д.
// Формат входных данных: Целое неотрицательное число

int main(void)
{
    uint32_t n=0,result=0;
    uint8_t num=0;

    scanf("%u", &n);

    while(n)
    {
        num = n%10;
        result = result*10 + num; 
        n /=10;
    }

    printf("%u\n", result);

    return 0;
}
