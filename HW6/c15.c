#include <inttypes.h>
#include <stdio.h>

/*Цифры по возрастанию
Составить функцию логическую функцию, которая определяет, верно ли, что в заданном числе все цифры стоят по возрастанию. Используя данную функцию решить задачу. 

int grow_up(int n)

Формат входных данных: Одно целое не отрицательное число
Формат результата: YES или NO
*/

uint8_t grow_up(uint32_t n);

int main(void)
{
    uint32_t n = 0;
    scanf("%u", &n);
    printf("%s\n", grow_up(n) ? "YES" : "NO");
    return 0;
}

uint8_t grow_up(uint32_t n)
{
    uint8_t tmp = n % 10;

    while (n) {
        n /= 10;
        if (n % 10 >= tmp)
            return 0;
        tmp = n % 10;
    }

    return 1;
}