#include <math.h>
#include <stdio.h>

/*Вычислить sin как сумма ряда.
-----------------------------------
Составить функцию, которая вычисляет синус как сумму ряда (с точностью 0.001):
sin(x) = x - x3/3! + x5/5! - x7/7! + ...(x в радианах)
float sinus(float x)

Формат входных данных: Одно число от 0 до 90

Формат результата: Вещественное число в формате "%.3f"
*/

const float PI = 3.1415926535;

float sinus(float x);

int main(void)
{
    float x = 0.0;
    scanf("%f", &x);

    x *= PI / 180.0;

    printf("%.3f\n", sinus(x));

    return 0;
}

float sinus(float x)
{
    float Xn = x;
    float sum = 0.0;
    int i = 1;

    do {
        sum += Xn;
        Xn *= -1.0 * x * x / ((2 * i) * (2 * i + 1));
        i++;
    } while (fabs(Xn) > 0.001);

    return sum;
}