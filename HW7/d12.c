#include <inttypes.h>
#include <stdio.h>

/*Монотонная последовательность
Дана монотонная последовательность, в которой каждое натуральное число k встречается ровно k раз: 1, 2, 2, 3, 3, 3, 4, 4, 4, 4,…
Выведите первые n членов этой последовательности.

Формат входных данных: Натуральное число.
Формат результата: Последовательность целых чисел.
*/

void generat_sequence(uint32_t n, int8_t k);

int main(void)
{
    int8_t k = 0;
    scanf("%hhd", &k);
    generat_sequence(1, k);
    return 0;
}

void generat_sequence(uint32_t n, int8_t k)
{
    if (k < 1)
        return;

    for (int32_t i = 1; i <= n && k > 0; i++) {
        printf("%u ", n);
        k--;
    }

    generat_sequence(n + 1, k);
}
