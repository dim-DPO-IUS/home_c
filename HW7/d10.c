#include <inttypes.h>
#include <stdio.h>

/*Проверка на простоту
Дано натуральное число n ≥ 1. Проверьте, является ли оно простым. Программа должна вывести слово YES, если число простое или NO в противном случае. Необходимо составить рекурсивную функцию и использовать ее.

int is_prime(int n, int divider)

Формат входных данных: Натуральное число
Формат результата: YES или NO
*/

uint8_t is_prime(uint32_t n, uint32_t divider);

int main(void)
{
    uint32_t n = 0, divider = 2;
    scanf("%u", &n);
    printf("%s\n", is_prime(n, divider)?"YES":"NO");
    return 0;
}

uint8_t is_prime(uint32_t n, uint32_t divider)
{
    if (n <= 1)
        return 0;

    if (divider == n)
        return 1;

    if (n % divider == 0)
        return 0;

    return is_prime(n, divider + 1);
}
