#include <inttypes.h>
#include <stdio.h>

/*В обратном порядке
Дано целое не отрицательное число N. Выведите все его цифры по одной, в обратном порядке, разделяя их пробелами или новыми строками.
Формат входных данных: Одно не отрицательное целое число
Формат результата: Последовательность цифр введенного числа в обратном порядке через пробел
*/

void print_revers(uint32_t n);

int main(void)
{
    uint32_t n = 0;
    scanf("%u", &n);
    print_revers(n);
    return 0;
}

void print_revers(uint32_t n)
{
    if (n < 10)
        printf("%d ", n);
    else {
        printf("%d ", n % 10);
        print_revers(n / 10);
    }
}
