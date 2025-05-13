#include <inttypes.h>
#include <stdio.h>

// Ввести целое число и определить, верно ли, что в его записи есть две одинаковые цифры, НЕ обязательно стоящие рядом.

int main(void)
{
    int32_t n = 0;

    scanf("%d", &n);
    n = n < 0 ? n * -1 : n;

    int32_t m = n;
    int8_t result = 0, num2 = 0, num1 = 0;

    while (n >= 10) {
        num1 = n % 10;
        m = n / 10;
        while (m) {
            num2 = m % 10;
            if (num1 == num2) {
                result = 1;
                break;
            }
            m /= 10;
        }
        if (result)
            break;
        n /= 10;
    }

    printf("%s\n", result ? "YES" : "NO");

    return 0;
}