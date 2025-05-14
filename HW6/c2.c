#include <inttypes.h>
#include <stdio.h>

/*Составить функцию, возведение числа N в степень P. int power(n, p) и привести
пример ее использования.
Формат входных данных: Два целых числа: N по модулю не превосходящих 1000 и P ≥ 0
Формат результата: Одно целое число
*/

int64_t power(int16_t n, uint32_t p);

int main(void)
{
    int16_t n = 0;
    uint32_t p = 0;

    scanf("%hd %u", &n, &p);
    printf("%ld\n", power(n, p));

    return 0;
}

int64_t power(int16_t n, uint32_t p)
{
    int64_t ret = 1;

    for (uint32_t i = 0; i < p; i++) {
        ret = ret * n;
    }

    return ret;
}