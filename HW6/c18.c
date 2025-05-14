#include <inttypes.h>
#include <stdio.h>

/*Количество цифр в тексте
Составить логическую функцию, которая определяет, что текущий символ это цифра. Написать программу считающую количество цифр в тексте. 

int is_digit(char c)

Формат входных данных: Текст из английских букв и знаков препинания. В конце текста символ точка.

Формат результата: Одно целое число - количество цифр в тексте.
*/

uint8_t is_digit(char c);

int main(void)
{
    char c;
    uint8_t sum_num = 0;

    while (c != '.') {
        scanf("%c", &c);
        is_digit(c) ? sum_num++ : sum_num;
    }
    printf("%hhu\n", sum_num);

    return 0;
}

uint8_t is_digit(char c)
{
    return c >= '0' && c <= '9' ? 1 : 0;
}