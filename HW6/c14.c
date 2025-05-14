#include <inttypes.h>
#include <stdio.h>

/*Сумма цифр четна.
Составить логическую функцию, которая определяет, верно ли, что сумма цифр числа – четное число. Используя эту функцию решить задачу.
Формат входных данных: Одно целое не отрицательное число
Формат результата: Ответ YES или NO
*/

void isEven(uint32_t n);

int main(void)
{
    uint32_t n = 0;
    scanf("%u", &n);
    isEven(n);
    return 0;
}

void isEven(uint32_t n)
{
    int32_t sum = 0;

    while (n) {
        sum += n % 10;
        n /= 10;
        if (!n)
            break;
    }
    printf("%s\n", sum % 2 == 0 ? "YES" : "NO");
}