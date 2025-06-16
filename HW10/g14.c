#include <stdio.h>

/*Hello name
В файле input.txt в одной строке фамилию, имя и отчество. Сформировать файл
приветствие output.txt, где останутся имя и фамилия
Формат входных данных Строка состоящая из английских букв и пробелов не более
100 символов.
Формат: Фамилия Имя Отчество Формат результата Строка состоящая из
английских букв и пробелов*/

#define MAX_LENGTH 100
const char *input_file = "input.txt";
const char *output_file = "output.txt";

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
    char surname[MAX_LENGTH] = {'\0'};
    char name[MAX_LENGTH] = {'\0'};
    fscanf(input, "%99s %99s", surname, name);
    fprintf(output, "%s %s %s%c", "Hello,", name, surname, '!');

    //---------------------------
    fclose(input);
    fclose(output);
    return 0;
}

//-----------------------------------------------------
