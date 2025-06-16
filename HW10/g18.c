#include <stdio.h>

/*Удалить пробелы из текста
В файле input.txt необходимо удалить все лишние пробелы (в начале предложения и
сдвоенные пробелы). Для решения задачи разработать функцию. Результат записать в
output.txt. Формат входных данных Строка из английских букв, знаков препинания и
пробелов. Не более 1000 символов. Формат результата Строка из английских букв,
знаков препинания и пробелов.*/

const char *input_file = "input.txt";
const char *output_file = "output.txt";
//
void trim_spaces(FILE *input, FILE *output);

//-----------------------------------------------------
int main(void)
{
    FILE *input = fopen(input_file, "r");
    FILE *output = fopen(output_file, "w");
    if (input == NULL || output == NULL)
    {
        perror("Ошибка открытия файла");
        return 1;
    }
    //---------------------------
    trim_spaces(input, output);
    //---------------------------
    fclose(input);
    fclose(output);
    return 0;
}

//-----------------------------------------------------

void trim_spaces(FILE *input, FILE *output)
{
    int c;
    while (fscanf(input, "%*[ ]") != EOF)
    {
        while ((c = fgetc(input)) != EOF && c != ' ')
            fputc(c, output);

        if (c == EOF) break;
        fputc(' ', output);
    }
}