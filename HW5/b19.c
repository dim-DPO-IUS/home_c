#include <inttypes.h>
#include <stdio.h>

// Ввести натуральное число и определить, верно ли, что сумма его цифр равна 10.
// Формат входных данных: Натуральное число
// Формат результата: YES или NO

int main(void)
{
    uint32_t n = 0;
    uint32_t sum = 0;

    scanf("%u", &n);

    while (n) {
        sum += n % 10;
        n /= 10;
    }

    printf("%s\n", sum == 10 ? "YES" : "NO");

    return 0;
}