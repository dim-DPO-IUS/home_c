#include <inttypes.h>
#include <stdio.h>

/*Строка наоборот
Дана строка заканчивающаяся символом точка '.' Напечатать строку наоборот. Реализуйте рекурсивную функцию, которая считывает и печатает строку наоборот.

void reverse_string()

Формат входных данных: Строка из английских букв и знаков препинания. В конце строки символ точка.
Формат результата: Исходная строка задом наперед.
*/

void reverse_string();

int main(void)
{
    reverse_string();
    return 0;
}

void reverse_string()
{
    char ch;
    if ((ch = getchar()) == '.')
        return;
    
    reverse_string();

    printf("%c", ch);
}
