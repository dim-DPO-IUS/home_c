#include <stdio.h>

/*Ling заменить на Cao
В файле input.txt дано предложение. Необходимо заменить все имена «Ling» на
«Cao» и результат записать в файл output.txt. Формат входных данных Строка из
английских букв, пробелов и знаков препинания. Не более 1000 символов. Формат
результата Строка из английских букв, пробелов и знаков препинания.*/

#define MAX_LENGTH 1001
const char *input_file = "input.txt";
const char *output_file = "output.txt";

// Замена слова в тексте: "Ling" заменяет его на "Cao"
void replace_ling_to_cao(FILE *input, FILE *output, int length);

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
    replace_ling_to_cao(input, output, MAX_LENGTH);
    //---------------------------
    fclose(input);
    fclose(output);
    return 0;
}

//-----------------------------------------------------

void replace_ling_to_cao(FILE *input, FILE *output, int length)
{
    char buffer[length];
    int i = 0;
    int c;

    while ((c = fgetc(input)) != EOF && i < length - 1)
    {
        buffer[i++] = c;

        // Проверяем последние 4 символа на "Ling"
        if (i >= 4 && buffer[i - 4] == 'L' && buffer[i - 3] == 'i' &&
            buffer[i - 2] == 'n' && buffer[i - 1] == 'g')
        {
            // Заменяем "Ling" на "Cao"
            i -= 4; // Возвращаемся на позицию перед "Ling"
            fwrite(buffer, 1, i, output); // Выводим все что до "Ling"
            fputs("Cao", output);         // Выводим замену
            i = 0;                        // Сбрасываем буфер
        }
    }

    // Выводим оставшиеся символы
    if (i > 0)
    {
        fwrite(buffer, 1, i, output);
    }
}
