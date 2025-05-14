#include <inttypes.h>
#include <stdio.h>

/*НОД
Составить функцию, которая определяет наибольший общий делитель двух натуральных и привести пример ее использования. int nod(int a, int b)
Формат входных данных: Два целых положительных числа
Формат результата: Одно целое число - наибольший общий делитель.
*/

uint32_t nod(uint32_t a, uint32_t b);

int main(void)
{
    uint32_t a = 0, b = 0;
    scanf("%u%u", &a, &b);
    printf("%u\n", nod(a, b));
    return 0;
}

uint32_t nod(uint32_t a, uint32_t b)
{
    while (a && b) {
        if (a >= b)
            a %= b;
        else
            b %= a;
    }

    return a == 0 ? b : a;
}