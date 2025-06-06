
#include <inttypes.h>
#include <stdio.h>

/*Цифры по возрастанию
Написать функцию и программу демонстрирующую работу данной функции. Вывести в
порядке возрастания цифры, входящие в десятичную запись натурального числа N, не
более 1000 цифр. Цифра пробел сколько раз данная цифра встречается в числе.
Формат входных данных: Натуральное число не более 1000 цифр
Формат результата: Цифры входящие в число через пробел в порядке возрастания. От
самой младшей цифры до самой старшей и количество.*/

enum
{
    SIZE = 1000
};

// Частота встречаемости цифры в числе
// num[] - число в виде массива символов
// arr[] - возвращаемый массив индексов и частот
void digit_frequency(char num[], int8_t out[]);

// Печать массива частот цифр числа
void print_digit_freq(int8_t arr[]);

// Ввод строки цифр
void input_digit(char num[], int16_t size);

int main(void)
{
    int8_t out[10] = {0};
    char num[SIZE + 1]; // SIZE цифр + '\0'
    input_digit(num, SIZE);
    digit_frequency(num, out);
    print_digit_freq(out);
    return 0;
}

//---------------------------------

void input_digit(char num[], int16_t size)
{
    int ch;
    int i = 0;
    while ((ch = getchar()) != '\n' && ch != EOF && i < size)
    {
        num[i++] = (char)ch;
    }
    num[i + 1] = '\0';
}

void print_digit_freq(int8_t arr[])
{
    for (int i = 0; i < 10; i++)
    {
        if (arr[i] > 0) printf("%d %d\n", i, arr[i]);
    }
}

void digit_frequency(char num[], int8_t out[])
{
    out[0] = -1;
    while (*num != '\0')
    {
        char dig = *num - '0';
        out[dig] <= 0 ? out[dig] = 1 : out[dig]++;
        num++;
    }
}