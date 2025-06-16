#include <stdio.h>

/*Проверка на палиндром
В файле input.txt символьная строка не более 1000 символов. Необходимо
проверить, является ли она палиндромом (палиндром читается одинаково в обоих
направлениях).

Реализовать логическую функцию:

is_palindrom(str)

и записать ответ в файл output.txt.

Формат входных данных: Строка из заглавных английских букв
Формат результата: YES или NO*/

#define MAX_INPUT_SIZE 1001
const char *input_file = "input.txt";
const char *output_file = "output.txt";

int is_palindrom(char str[], int size);

int main(void)
{
    //---------------------
    FILE *input = fopen(input_file, "r");
    FILE *output = fopen(output_file, "w");

    if (input == NULL || output == NULL)
    {
        perror("Ошибка открытия файла");
        return 1;
    }
    //---------------------
    char str[MAX_INPUT_SIZE] = {'\0'};
    fscanf(input, "%1000[^\n\r]", str);
    int size = 0;
    for (size = 0; str[size] != '\0'; size++)
        ;
    fprintf(output, "%s", is_palindrom(str, size) ? "YES" : "NO");
    //---------------------
    fclose(input);
    fclose(output);

    return 0;
}

int is_palindrom(char str[], int size)
{
    int yes_no = 1; // 1 - yes, 0 - no
    for (int i = 0; i < size / 2; i++)
    {
        if (str[i] != str[size - i - 1])
        {
            yes_no = 0;
            break;
        }
    }
    return yes_no;
}