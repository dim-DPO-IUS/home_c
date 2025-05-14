#include <inttypes.h>
#include <stdio.h>

/*
Факториал. Составить функцию вычисления N!. Использовать ее при вычислении факториала int factorial(int n)
Формат входных данных: Целое положительное число не больше 20
Формат результата: Целое положительное число
*/

int32_t factorial(int32_t n);

int main(void)
{
    int32_t n = 0;
    scanf("%d", &n);
    printf("%d\n", factorial(n));
    return 0;
}

int32_t factorial(int32_t n)
{
    int32_t fact = 1;

    for (int32_t i = 1; i <= n; i++) {
        fact *= i;
    }

    return fact;
}
