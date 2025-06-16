#include <stdio.h>

/*Изменить расширение
В файле input.txt записан полный адрес файла (возможно, без расширения).
Необходимо изменить его расширение на ".html" и записать результат в файл
output.txt.
Формат входных данных Строка состоящая из символов: a-z, A-Z, 0-9, /
Формат результата Исходная строка с измененным расширением.*/

const char *input_file = "input.txt";
const char *output_file = "output.txt";

// Соответствует ли расширение эталону
// ext[]: строка расширения с ведущей точкой
// size_ext: размер строки расширения, не учитывая '\0'
// ВОЗВРАТ:
//      значение <0: расширение уже соотв. эталону
//      значение >0: расширения либо нет, либо не соотв. эталону
// Значение >0 - это позиция указателя (индекс символа) с которой нужно
// дописывать/переписывать правильное расширение.
int check_extension(FILE *input, char ext[], int size_ext);

#define EXT ".html"
#define SIZE_EXT 5 // размер строки расширения без '\0'

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
    char html[SIZE_EXT] = EXT;
    // Проверка расширения
    int pos = check_extension(input, html, SIZE_EXT);
    // Если расширение неправильное или отсутствует
    if (pos > 0)
    {
        for (int i = 0; i < pos; i++) // Записать не изменяемую часть строки
        {
            char c = fgetc(input);
            if (c != '\r' && c != '\n') fputc(c, output);
        }

        for (int i = 0; i < SIZE_EXT; i++) // Дописать расширение
            fputc(EXT[i], output);
    }
    else // Если расширение правильное
    {
        for (int i = 0; i < -pos; i++)
            fputc(fgetc(input), output);
    }

    //---------------------------
    fclose(input);
    fclose(output);
    return 0;
}

//-----------------------------------------------------

int check_extension(FILE *input, char ext[], int size_ext)
{
    fseek(input, -1, SEEK_END); // Начинаем с последнего символа
    int pos = ftell(input);
    char c, err = -1; // -1: нет ошибки, 1: ошибка
    while (pos >= 0)
    {
        c = fgetc(input);
        if (err == -1 && c != ext[--size_ext]) err = 1;
        if (c == '/' || c == '.') break;
        fseek(input, (--pos), SEEK_SET);
    }
    // Расширение соответствует эталону или расширение отсутствует
    if (err == -1 || c == '/')
    {
        fseek(input, 0, SEEK_END);
        pos = ftell(input) * err;
    }
    rewind(input);
    return pos;
}