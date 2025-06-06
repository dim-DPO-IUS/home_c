#include <inttypes.h>
#include <stdio.h>

// Составить программу для вычисления НОД с помощью алгоритма Евклида. Даны два натуральных числа. Найти наибольший общий делитель.
// Формат входных данных: Два неотрицательных целых числа

int main(void)
{
    uint32_t a = 0, b = 0;

    scanf("%u%u", &a, &b);

    while (a && b) {
        if (a >= b)
            a %= b;
        else
            b %= a;
    }

    printf("%u\n", a == 0 ? b : a);
    return 0;
}