#include <inttypes.h>
#include <stdio.h>

// Ввести два целых числа a и b (a ≤ b) и вывести квадраты всех чисел от a до b.

int main(void)
{
    int8_t a = 0, b = 0;

    scanf("%hhd%hhd", &a, &b);

    for (int i = a; i <= b; i++)
        printf("%d ", i * i);

    return 0;
}