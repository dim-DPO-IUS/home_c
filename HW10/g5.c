#include <stdio.h>

/*Заменить a на b
В файле input.txt дана символьная строка не более 1000 символов. Необходимо
заменить все буквы "а" на буквы "b" и наоборот, как заглавные, так и строчные.
Результат записать в output.txt.
Формат входных данных Строка из маленьких и
больших английских букв, знаков препинания и пробелов.
Формат результата Строка
из маленьких и больших английских букв, знаков препинания и пробелов.*/


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
    int ch;
    while ((ch = fgetc(input)) != EOF && ch != '\n' && ch != '\r' && ch != '\0')
    {
        if (ch == 'a' || ch == 'A')
            ch++;
        else if (ch == 'b' || ch == 'B')
            ch--;

        fprintf(output, "%c", ch);
    }

    //---------------------
    fclose(input);
    fclose(output);

    return 0;
}
// ------------------------------------------------
