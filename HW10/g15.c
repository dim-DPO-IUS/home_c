#include <stdio.h>

/*Cao заменить на Ling
В файле input.txt дано предложение. Необходимо заменить все имена «Cao» на
«Ling» и записать результат в файл output.txt.

Формат входных данных Строка из английский букв, знаков препинания и пробелов.
Не более 1000 символов.

Формат результата Строка из английский букв, знаков препинания и пробелов.*/

#define MAX_LENGTH 1001
const char *input_file = "input.txt";
const char *output_file = "output.txt";

// Замена слова в тексте: Заменяем "Cao" на "Ling"
void replace_cao_to_ling(FILE *input, FILE *output, int length);

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
    replace_cao_to_ling(input, output, MAX_LENGTH);
    //---------------------------
    fclose(input);
    fclose(output);
    return 0;
}

//-----------------------------------------------------

void replace_cao_to_ling(FILE *input, FILE *output, int length)
{
    char buffer[length];
    int i = 0;
    int c;

    while ((c = fgetc(input)) != EOF && i < length - 1)
    {
        buffer[i++] = c;

        // Проверяем последние 3 символа на "Cao"
        if (i >= 3 && buffer[i - 3] == 'C' && buffer[i - 2] == 'a' &&
            buffer[i - 1] == 'o')
        {
            // Заменяем "Cao" на "Ling"
            i -= 3; // Возвращаемся на позицию перед "Cao"
            fwrite(buffer, 1, i, output); // Выводим все что до "Cao"
            fputs("Ling", output);        // Выводим замену
            i = 0;                        // Сбрасываем буфер
        }
    }

    // Выводим оставшиеся символы
    if (i > 0)
    {
        fwrite(buffer, 1, i, output);
    }
}