#include <inttypes.h>
#include <stdio.h>

/*От 1 до N
Составить рекурсивную функцию, печать всех чисел от N до 1.
Формат входных данных: Одно натуральное число
Формат результата: Последовательность целых чисел от введенного числа до 1, через пробел.
*/

void print_revers(uint32_t n);

int main(void)
{
    uint32_t n = 0;
    scanf("%u", &n);
    print_revers(n);
    return 0;
}

void print_revers(uint32_t n)
{
    if (n < 1)
        return;
    printf("%u ", n);
    print_revers(n - 1);
}
