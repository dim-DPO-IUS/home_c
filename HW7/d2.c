#include <inttypes.h>
#include <stdio.h>

/*Сумма чисел от 1 до N
Составить рекурсивную функцию, которая определяет сумму всех чисел от 1 до N
Формат входных данных: Одно натуральное число
Формат результата: Сумма чисел от 1 до введенного числа
*/

int32_t sumN(int32_t n);

int main(void)
{
    int32_t n = 0;
    scanf("%d", &n);
    printf("%d\n", sumN(n));
    return 0;
}

int32_t sumN(int32_t n)
{
    if (n < 1)
        return 0;

    return n + sumN(n - 1);
}
