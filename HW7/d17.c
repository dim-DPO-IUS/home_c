#include <inttypes.h>
#include <stdio.h>

/*Функция Аккермана

Реализуйте данную функцию по прототипу

int akkerman(int m, int n)

Формат входных данных: Даны неотрицательные целые числа m и n
Формат результата: Одно целое число*/

int64_t akkerman(uint32_t m, uint32_t n);

int main(void)
{
    uint32_t m = 0, n = 0;
    scanf("%u%u", &m, &n);
    printf("%ld\n", akkerman(m, n));
    return 0;
}

int64_t akkerman(uint32_t m, uint32_t n)
{
    if (m == 0)
        return n + 1;

    if (n == 0)
        return akkerman(m - 1, 1);

    return akkerman(m - 1, akkerman(m, n - 1));
}
