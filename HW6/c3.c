#include <inttypes.h>
#include <stdio.h>

/* Написать функцию, которая возвращает среднее арифметическое двух переданных ей аргументов (параметров). int middle(int a, int b)
Формат входных данных: Два целых не отрицательных числа
Формат результата: Одно целое число
*/

int middle(int a, int b);

int main(void)
{
    int a = 0, b = 0;
    scanf("%d%d", &a, &b);
    printf("%d\n", middle(a, b));
    return 0;
}

int middle(int a, int b)
{
    int average = 0;
    average = (a + b) / 2;
    return average;
}