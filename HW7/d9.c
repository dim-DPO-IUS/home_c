#include <inttypes.h>
#include <stdio.h>

/*Сумма цифр числа
Дано натуральное число N. Вычислите сумму его цифр. Необходимо составить рекурсивную функцию.

int sum_digits(int n)

Формат входных данных: Одно натуральное число.
Формат результата: Целое число - сумма цифр введенного числа.
*/

uint8_t sum_digits(uint32_t n);

int main(void)
{
    uint32_t n = 0;
    scanf("%u", &n);
    printf("%hhu", sum_digits(n));
    return 0;
}

uint8_t sum_digits(uint32_t n)
{
    if (n < 10)
        return n;
    else
        return sum_digits(n / 10) + (n % 10);
}
