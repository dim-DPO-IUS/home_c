#include <inttypes.h>
#include <stdio.h>

/*Описать функцию вычисления f(x) по формуле:
f(x)= x*x при -2 ≤ x < 2;
x*x+4x+5 при x ≥ 2;
4 при x < -2.

Используя эту функцию для n заданных чисел, вычислить f(x). Среди вычисленных значений найти наибольшее.

Формат входных данных: Последовательность не нулевых целых чисел, в конце последовательности число 0.

Формат результата: Одно целое число
*/

int32_t func(int32_t num);

int main(void)
{
    int32_t num = 1, ret_func = 0, max = 0;

    while (num) {
        scanf("%d", &num);
        if (!num)
            break;
        ret_func = func(num);
        max = ret_func > max ? ret_func : max;
    }

    printf("%d\n", max);
    return 0;
}

int32_t func(int32_t num)
{
    int32_t ret = 0;

    if (num < -2)
        ret = 4;
    else if (num >= 2)
        ret = num * num + 4 * num + 5;
    else
        ret = num * num;

    return ret;
}
