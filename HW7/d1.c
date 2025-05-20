#include <inttypes.h>
#include <stdio.h>

/*От 1 до N
Составить рекурсивную функцию, печать всех чисел от 1 до N
Формат входных данных: Одно натуральное число
Формат результата: Последовательность чисел от 1 до введенного числа
*/

void printN(uint32_t i, uint32_t N);

int main(void)
{
    uint32_t i = 1, N = 0;
    scanf("%u", &N);
    printN(i, N);
    return 0;
}

void printN(uint32_t i, uint32_t N)
{
    if (i > N)
        return;

    printf("%u ", i);

    printN(i + 1, N);
}
