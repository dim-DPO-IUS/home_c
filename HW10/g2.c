
#include <stdio.h>

/*Строка и цифры
Считать число N из файла input.txt. Сформировать строку из N символов. N четное
число, не превосходящее 26. На четных позициях должны находится четные цифры в
порядке возрастания, кроме 0, на нечетных позициях - заглавные буквы в порядке
следования в английском алфавите. Результат записать в файл output.txt

Формат входных данных: Четное N ≤ 26
Формат результата: Строка из английских букв и цифр*/

const char *input_file = "input.txt";
const char *output_file = "output.txt";

int main(void)
{
    //---------------------
    FILE *input = fopen(input_file, "r");
    FILE *output = fopen(output_file, "w");
    // Проверка на ошибку открытия файла
    if (input == NULL || output == NULL)
    {
        perror("Ошибка открытия файла");
        return 1;
    }
    //---------------------
    int n = 0;
    fscanf(input, "%d", &n);
    char str[n + 1];
    char letter = 'A';
    char dig = '2';
    for (int i = 0; i < n; i++)
    {
        if (i % 2 == 0)
            str[i] = letter++;
        else
        {
            str[i] = dig;
            dig += 2;
            if (dig > '8') dig = '2';
        }
    }
    str[n] = '\0';
    fprintf(output, "%s", str);
    //---------------------
    fclose(input);
    fclose(output);

    return 0;
}