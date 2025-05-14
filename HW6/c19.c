#include <inttypes.h>
#include <stdio.h>

/*Сумма цифр в тексте
Составить функцию, которая преобразует текущий символ цифры в число. Написать программу считающую сумму цифр в тексте. 

int digit_to_num(char c)

Формат входных данных: Строка состоящая из английских букв, пробелов, знаков препинания. В конце строки символ точка.
Формат результата: Целое число - сумма цифр в тексте
*/

uint8_t digit_to_num(char c);

int main(void)
{
    char c;
    uint8_t sum = 0;

    while (c != '.') {
        scanf("%c", &c);
        sum += digit_to_num(c);
    }
    printf("%hhu\n", sum);
    return 0;
}

uint8_t digit_to_num(char c)
{
    return c >= '0' && c <= '9' ? c - '0' : 0;
}