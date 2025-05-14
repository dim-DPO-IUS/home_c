#include <inttypes.h>
#include <stdio.h>

/*Простые множители
Составить функцию, печать всех простых множителей числа. Использовать ее для печати всех простых множителей числа. void print_simple(int n)
Формат входных данных: Целое положительное число.
Формат результата: Последовательность всех простых множителей данного числа в порядке возрастания.
*/

void print_simple(uint32_t n);

int main(void)
{
    uint32_t n;
    scanf("%u", &n);
    print_simple(n);
    return 0;
}

void print_simple(uint32_t n)
{
    uint32_t div = 2;
    while (n != 1) {
        if (n % div == 0) {
            printf("%d ", div);
            n /= div;
        } else
            div++;
    }
}
