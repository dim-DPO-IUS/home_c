#include <inttypes.h>
#include <stdio.h>

/*Печать простых множителей
Составить рекурсивную функцию, печать всех простых множителей числа.
Формат входных данных: Натуральное число
Формат результата: Последовательность из всех простых делителей числа через пробел
*/

void print_prime(uint32_t n);

int main(void)
{
    uint32_t n = 0;
    scanf("%u", &n);
    print_prime(n);
    return 0;
}

void print_prime(uint32_t n)
{
    if (n <= 1)
        return;

    if (n % 2 == 0) {
        printf("%u ", 2);
        print_prime(n / 2);
        return;
    }

    for (uint32_t i = 3; i * i <= n; i += 2) {
        if (n % i == 0) {
            printf("%u ", i);
            print_prime(n / i);
            return;
        }
    }

    printf("%u ", n);
}
