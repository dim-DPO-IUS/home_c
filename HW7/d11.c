#include <inttypes.h>
#include <stdio.h>

/*Количество 1
Дано натуральное число N. Посчитать количество «1» в двоичной записи числа.

Формат входных данных: Натуральное число
Формат результата: Целое число - количество единиц в двоичной записи числа. */

uint8_t number_1(uint32_t n);

int main(void)
{
    uint32_t n = 0;
    scanf("%u", &n);
    printf("%u\n", number_1(n));
    return 0;
}

uint8_t number_1(uint32_t n)
{
    if (n == 0)
        return 0;

    return number_1(n / 2) + n % 2;
}
