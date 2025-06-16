#include <stdio.h>

/*В файле input.txt дано предложение. Необходимо определить, сколько слов
заканчиваются на букву 'а'. Ответ записать в файл output.txt.
Формат входных данных: Строка из английских букв и пробелов не более 1000
символов.
Формат результата: Одно целое число*/

const char *input_file = "input.txt";
const char *output_file = "output.txt";

// Сколко слов заканчивается на букву 'letter'
int words_ending_with(FILE *input, char letter);

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
    int cnt = words_ending_with(input, 'a');
    fprintf(output, "%d ", cnt);

    //---------------------------
    fclose(input);
    fclose(output);
    return 0;
}

//-----------------------------------------------------

int words_ending_with(FILE *input, char letter)
{
    int cnt = 0;
    while (fscanf(input, "%*s") != EOF)
    {
        fseek(input, -1, SEEK_CUR);
        fgetc(input) == 'a' ? cnt++ : cnt;
        fseek(input, 1, SEEK_CUR);
    }
    return cnt;
}