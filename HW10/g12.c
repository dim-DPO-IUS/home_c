#include <stdio.h>

/*Разобрать на слова
В файле input.txt дано предложение требуется разобрать его на отдельные слова.
Напечатать каждое слово на отдельной строке в файл output.txt.
Формат входных данных Одна строка из английских букв и пробелов не более 1000
символов.
Формат результата Каждое слово на отдельной строке*/

const char *input_file = "input.txt";
const char *output_file = "output.txt";
// Проверка на принадлежность символа к буквам
int is_letter(char c);

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
    int c;
    int in_word = 0; // Флаг, указывающий, что мы внутри слова

    while ((c = fgetc(input)) != EOF)
    {
        if (is_letter(c)) 
        {
            fputc(c, output);
            in_word = 1; 
        }
        else if (in_word) // Если это не буква, но мы были в слове
        {
            fputc('\n', output); 
            in_word = 0;         
        }
    }

    // Если файл заканчивается словом (без пробела в конце)
    if (in_word)
        fputc('\n', output);

    //---------------------------
    fclose(input);
    fclose(output);
    return 0;
}

//-----------------------------------------------------

int is_letter(char c)
{
    return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z');
}