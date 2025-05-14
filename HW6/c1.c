#include <inttypes.h>
#include <stdio.h>
/*
Составить функцию, модуль числа и привести пример ее использования.
Формат входных данных: Целое число
Формат результата: Целое не отрицательное число
*/

int32_t abs(int32_t num);

int main(void)
{
    int32_t num = 0;

    scanf("%d", &num);
    printf("%d\n", abs(num));

    return 0;
}

int32_t abs(int32_t num)
{
    int32_t abs_num = 0;
    abs_num = num >= 0 ? num : -num;
    return abs_num;
}