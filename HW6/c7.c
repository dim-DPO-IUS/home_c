#include <inttypes.h>
#include <stdio.h>

/*Составить функцию, которая переводит число N из десятичной системы счисления в P-ичную систему счисления.
Формат входных данных: Два целых числа. N ≥ 0 и 2 ≤ P ≤ 9
Формат результата: Одно целое число
*/

uint32_t fromDecimal(uint32_t decimal, uint8_t base);

int main(void)
{
    uint32_t decimal = 0;
    uint8_t base = 2;

    scanf("%u %hhu", &decimal, &base);
    printf("%u\n", fromDecimal(decimal, base));
    return 0;
}

// Функция для перевода из десятичной СС в другую (2 - 9)
uint32_t fromDecimal(uint32_t decimal, uint8_t base)
{
    uint32_t result = 0;
    uint32_t digit = 1;
    uint32_t remainder = 0;

    if (decimal == 0) {
        result = 0;
    } else {
        while (decimal > 0) {
            remainder = decimal % base;
            remainder *= digit;

            result += remainder;

            decimal /= base;
            digit *= 10;
        }
    }

    return result;
}