#include <stdio.h>

/*Три раза
В файле input.txt дана строка. Вывести ее в файл output.txt три раза через
запятую и показать количество символов в ней.

Формат входных данных: Строка из английских букв и пробелов. Не более 100
символов. В конце могут быть незначащие переносы строк.

Формат результата: Исходная строка 3 раза подряд, через запятую пробел и
количество символов в ней.*/

#define MAX_INPUT_SIZE 100
const char *input_file = "input.txt";
const char *output_file = "output.txt";

int main(void)
{
    //---------------------
    FILE *input = fopen(input_file, "r");
    FILE *output = fopen(output_file, "w");
    // Проверка на ошибку открытия файла
    if (input == NULL || output == NULL)
    {
        perror("Ошибка открытия файла");
        return 1;
    }
    //---------------------
    char str[MAX_INPUT_SIZE] = {'\0'};
    int len = 0;
    int ch; // int для корректного распознавания EOF
    // Для Windows: ch != '\r'
    while ((ch = fgetc(input)) != EOF && ch != '\n' && ch != '\r' &&
           len < MAX_INPUT_SIZE)
    {
        str[len++] = (char)ch;
    }

    // Записываем строку 3 раза через ", "
    fprintf(output, "%s, %s, %s %d", str, str, str, len);
    //---------------------
    fclose(input);
    fclose(output);

    return 0;
}