#include <inttypes.h>
#include <stdio.h>

/*Составить функцию, которая определяет сумму всех чисел от 1 до N и привести пример ее использования.
Формат входных данных: Одно целое положительное число N
Формат результата: Целое число - сумма чисел от 1 до N
*/

int32_t sumN(int32_t n);

int main(void)
{
    int32_t n = 0, sum_n = 0;
    scanf("%d", &n);
    printf("%d\n", sumN(n));
    return 0;
}

int32_t sumN(int32_t n)
{
    int32_t ret = 0;
    for (int32_t i = 1; i <= n; i++) {
        ret += i;
    }
    return ret;
}