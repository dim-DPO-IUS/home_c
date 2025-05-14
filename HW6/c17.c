#include <inttypes.h>
#include <stdio.h>

/*Сумма цифр равна произведению
Составить логическую функцию, которая определяет, верно ли, что в заданном числе сумма цифр равна произведению. 

int is_happy_number(int n)

Формат входных данных: Целое не отрицательное число
Формат результата: YES или NO
*/

int8_t is_happy_number(uint32_t n);

int main(void)
{
    uint32_t n = 0;
    scanf("%u", &n);
    printf("%s\n", is_happy_number(n) ? "YES" : "NO");
    return 0;
}

int8_t is_happy_number(uint32_t n)
{
    int32_t sum = 0, mult = 1;

    while (n) {
        sum += n % 10;
        mult *= n % 10;
        n /= 10;
        if (!n)
            break;
    }

    return sum == mult ? 1 : 0;
}