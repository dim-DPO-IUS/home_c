#include <stdio.h>

/*Последний номер символа
В файле input.txt дана строка из не более 1000 символов. Показать номера
символов, совпадающих с последним символом строки. Результат записать в файл
output.txt
Формат входных данных Строка из не более 1000 символов
Формат результата Целые числа через пробел - номера символа, который совпадает
с последним символом строки.*/

#define MAX_INPUT_SIZE 1001
const char *input_file = "input.txt";
const char *output_file = "output.txt";

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
    int ch;

    int size = 0;
    while ((ch = fgetc(input)) != EOF && ch != '\n' && ch != '\r')
    {
        str[size++] = (char)ch;
    }

    char letter = str[size - 1];
    for (int i = 0; i < size - 1; i++)
    {
        if (str[i] == letter)
        {
            fprintf(output, "%d ", i);
        }
    }

    //---------------------
    fclose(input);
    fclose(output);

    return 0;
}
// ------------------------------------------------
