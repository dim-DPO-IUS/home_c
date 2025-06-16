#include <stdio.h>

/*Удалить повторяющиеся символы
В файле input.txt строка из меленьких и больших английских букв, знаков
препинания и пробелов. Требуется удалить из нее повторяющиеся символы и все
пробелы. Результат записать в файл output.txt.

Формат входных данных Строка из меленьких и больших английских букв, знаков
препинания и пробелов. Размер строки не более 1000 сивмолов.

Формат результата Строка из меленьких и больших английских букв.*/

#define MAX_SIZE 1001
const char *input_file = "input.txt";
const char *output_file = "output.txt";

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
    int ch;
    int used[127] = {0}; // английские буквы + знаки препинания - пробел
    while ((ch = fgetc(input)) != EOF && ch != '\n' && ch != '\r')
    {
        if (ch != ' ' && !used[ch])
        {
            used[ch]++;
            fputc(ch, output);
        }
    }
    //---------------------------
    fclose(input);
    fclose(output);
    return 0;
}

//-----------------------------------------------------
