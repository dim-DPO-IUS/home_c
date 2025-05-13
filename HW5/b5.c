#include <inttypes.h>
#include <stdio.h>

// Ввести целое число и найти сумму его цифр.
// Формат входных данных: Одно целое число большее или равное нулю.

int main(void)
{
    uint32_t a = 0;
    uint8_t sum = 0;

    scanf("%u", &a);

    while (a) {
        sum += a % 10;
        a /= 10;
    }

    printf("%hhu\n", sum);

    return 0;
}