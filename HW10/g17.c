#include <stdio.h>

/*Пары соседних символов
В файле input.txt записаны символы. Необходимо разработать функцию, которая
меняет местами пары соседних символов не обращая внимание на символы пробел.
Если количество символов нечетно (пробелы не считаем), то последний символ не
меняем. Результат записать в файл output.txt. Формат входных данных Строка из
английских букв, пробелов и знаков препинания. Не более 1000 символов. Формат
результата Строка из английских букв, пробелов и знаков препинания.*/

#define LENGTH 1001
const char *input_file = "input.txt";
const char *output_file = "output.txt";

void swap(char *a, char *b);

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
    char buffer[LENGTH];
    int size = 0;
    int c;

    // Читаем весь файл в буфер (максимум 1000 символов)
    while ((c = fgetc(input)) != EOF && c != '\n' && c != '\r' &&
           size < LENGTH - 1)
    {
        buffer[size++] = (char)c;
    }
    buffer[size] = '\0';

    int i = 0;
    while (i < size)
    {
        // Пропускаем пробелы
        if (buffer[i] == ' ')
        {
            i++;
            continue;
        }

        // Находим следующий не пробельный символ
        int j = i + 1;
        while (j < size && buffer[j] == ' ')
            j++;

        // Если нашли пару - меняем местами
        if (j < size && buffer[j] != ' ')
        {
            swap(&buffer[i], &buffer[j]);
            i = j + 1;
        }
        else
        {
            break; // Нечетное количество символов
        }
    }

    fprintf(output, "%s", buffer);
    //---------------------------
    fclose(input);
    fclose(output);
    return 0;
}

//-----------------------------------------------------
void swap(char *a, char *b)
{
    char tmp = *a;
    *a = *b;
    *b = tmp;
}
