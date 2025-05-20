#include <inttypes.h>
#include <stdio.h>

/*Возвести в степень
Написать рекурсивную функцию возведения целого числа n в степень p.

int recurs_power(int n, int p)

Используя данную функцию, решить задачу.

Формат входных данных: Два целых числа -100 ≤ n ≤ 100 и 0 ≤ p ≤ 100
Формат результата: Одно целое число n в степени p*/

int64_t recurs_power(int8_t n, uint8_t p);

int main(void)
{
    int8_t n = 0;
    uint8_t p = 0;
    scanf("%hhd %hhu", &n, &p);
    printf("%ld\n", recurs_power(n, p));
    return 0;
}

int64_t recurs_power(int8_t n, uint8_t p)
{
    int64_t rpow = 0;
    if (p == 0)
        return 1;

    rpow = recurs_power(n, p - 1) * n;
    return rpow;
}
