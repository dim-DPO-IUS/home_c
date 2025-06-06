#include <stdio.h>

/*Цифры в строке
Написать только одну функцию. Всю программу отправлять не надо. Вывести в
порядке возрастания цифры, входящие в строку. Цифра - количество. Функция должно
строго соответствовать прототипу:

void print_digit(char s[])

Формат входных данных: Строка из английских букв, пробелов, знаков препинания и
цифр Формат результата: Функция должна принмать на вход строку и выводить на
печать по формату: Цифра пробел количество.*/

enum
{
    SIZE = 100
};

// Считает и печатает цифры в числе
void print_digit(char s[]);

// Ввод строки
void input_digit(char str[], int size);

//------------------------------------

int main(void)
{
    char str[SIZE];
    input_digit(str, SIZE);
    print_digit(str);
    return 0;
}

//------------------------------------

void input_digit(char str[], int size)
{
    int ch;
    int i = 0;
    while ((ch = getchar()) != '\n' && ch != EOF && i < size)
    {
        str[i++] = (char)ch;
    }
    str[size] = '\0';
}

void print_digit(char s[])
{
    int digit_count[10] = {0};

    while (*s != '\0')
    {
        if (*s >= '0' && *s <= '9') digit_count[*s - '0']++;
        s++;
    }

    for (int i = 0; i < 10; i++)
    {
        if (digit_count[i] > 0) printf("%d %d\n", i, digit_count[i]);
    }
}