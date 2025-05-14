#include <inttypes.h>
#include <stdio.h>

/*Проверка на простоту
Составить функцию логическую функцию, которая определяет, верно ли, что число простое. Используя функцию решить задачу. 

int is_prime(int n)

Формат входных данных: Одно целое не отрицательное число.
Формат результата: YES или NO
*/

int8_t is_prime(uint32_t n);

int main(void)
{
    uint32_t n = 0;
    scanf("%u", &n);
    printf("%s\n", is_prime(n) ? "YES" : "NO");
    return 0;
}

int8_t is_prime(uint32_t n)
{
    int i = 2;

    if (n < 2 || n % 2 == 0 && n != 2)
        return 0;

    while (i * i <= n) {
        if (n % i == 0)
            return 0;
        i++;
    }
    return 1;
}