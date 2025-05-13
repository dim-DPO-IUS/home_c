#include <inttypes.h>
#include <stdio.h>

// Ввести натурально число и напечатать все числа от 10 до введенного числа - у которых сумма цифр равна произведению цифр
// Формат входных данных. Одно натуральное число большее 10

int main(void)
{
    uint32_t n = 0;

    scanf("%u", &n);

    for (int i = 10; i <= n; i++) {
        uint32_t j = i, sum = 0, mult = 1;
        while (j) {
            sum += j % 10;
            mult *= j % 10;
            j /= 10;
        }
        if (sum == mult)
            printf("%u ", i);
    }

    return 0;
}