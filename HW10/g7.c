#include <stdio.h>

/*Количество букв
В файле input.txt считать символьную строку, не более 10 000 символов.
Посчитать количество строчных (маленьких) и прописных (больших) букв в
введенной строке. Учитывать только английские буквы. Результат записать в файл
output.txt.
Формат входных данных Строка состоящая из английских букв, цифр,
пробелов и знаков препинания.
Формат результата Два целых числа. Количество строчных букв и количество
заглавных букв.*/

#define MAX_INPUT_SIZE 10001
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
    char str[MAX_INPUT_SIZE];
    fgets(str, sizeof(str), input);

    int lowercase = 0, uppercase = 0;

    for (int i = 0; str[i] != '\0'; i++)
    {
        if (str[i] >= 'a' && str[i] <= 'z')
        {
            lowercase++;
        }
        else if (str[i] >= 'A' && str[i] <= 'Z')
        {
            uppercase++;
        }
    }

    fprintf(output, "%d %d", lowercase, uppercase);
    //---------------------
    fclose(input);
    fclose(output);

    return 0;
}

//-----------------------------------------------------
