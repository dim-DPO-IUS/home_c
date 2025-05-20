#include <inttypes.h>
#include <stdio.h>

/*В двоичную систему
Перевести натуральное число в двоичную систему счисления. Необходимо реализовать рекурсивную функцию.
Формат входных данных: Целое не отрицательное число в десятичной системе счисления
Формат результата: Целое число в двоичной системе счисления
*/

uint32_t num_to_bin(uint32_t n);

int main(void)
{
    uint32_t n = 0;
    scanf("%u", &n);
    printf("%u ", num_to_bin(n));
    return 0;
}

uint32_t num_to_bin(uint32_t n)
{
    if (n == 0)
        return 0;

    return num_to_bin(n / 2) * 10 + n % 2;
}
