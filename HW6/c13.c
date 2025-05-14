#include <math.h>
#include <stdio.h>

/*Вычислить cos как сумма ряда
Составить функцию, которая вычисляет косинус как сумму ряда (с точностью 0.001)
cos(x) = 1 - x^2/2! + x^4/4! - x^6/6! + ... (x в радианах)

Прототип функции:
float cosinus(float x)

Формат входных данных: Целое число от 0 до 90
Формат результата: Вещественное число в формате "%.3f"*/

const float PI = 3.1415926535;

float cosinus(float x);

int main()
{
    float x = 0.0;
    scanf("%f", &x);

    x *= PI / 180.0;

    printf("%.3f\n", cosinus(x));
    return 0;
}

float cosinus(float x)
{
    float E, sum = 1.0, term = 1.0;
    int n = 0;
    // Цикл для вычисления cos через ряд Тейлора с точностью E
    while (fabs(term) > E) {
        n++;
        term *= -x * x / ((2 * n - 1) * (2 * n)); // Обновление члена ряда
        sum += term;                              // Суммирование ряда
    }

    return sum;
}