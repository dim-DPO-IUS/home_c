#include <inttypes.h>
#include <stdio.h>

/*Точная степень двойки
Написать логическую рекурсивную функцию и используя ее определить является ли введенное натуральное число точной степенью двойки.

int is2pow(int n)

Формат входных данных: Одно натуральное число.
Формат результата: YES или NO*/

int32_t is2pow(int32_t n);

int main(void)
{
    int32_t num = 0;
    scanf("%d", &num);

    printf("%s\n", is2pow(num) ? "YES" : "NO");
    return 0;
}

int32_t is2pow(int32_t n)
{
    if (n == 1)
        return 1;

    else if (n % 2 != 0 || n == 0)
        return 0;
    else 
        is2pow(n / 2);
}
