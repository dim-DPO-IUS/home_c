#include <inttypes.h>
#include <stdio.h>

/*В прямом порядке
Дано натуральное число N. Выведите все его цифры по одной, в прямом порядке, разделяя их пробелами или новыми строками. Необходимо реализовать рекурсивную функцию.

void print_num(int num)

Формат входных данных: Одно целое неотрицательное число
Формат результата: Все цифры числа через пробел в прямом порядке.*/

void print_num(uint32_t num);

int main(void)
{
    uint32_t num = 0;
    scanf("%u", &num);
    print_num(num);
    return 0;
}

void print_num(uint32_t num)
{
    if (num < 10)
        printf("%d ", num);
    else {
        print_num(num / 10);
        printf("%d ", num % 10);
    }
}
