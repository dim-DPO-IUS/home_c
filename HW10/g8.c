#include <stdio.h>
#include <stdlib.h>
/*Числа в массив
В файле input.txt дана строка, не более 1000 символов, содержащая буквы, целые
числа и иные символы. Требуется все числа, которые встречаются в строке,
поместить в отдельный целочисленный массив. Например, если дана строка "data 48
call 9 read13 blank0a", то в массиве числа 48, 9, 13 и 0. Вывести массив по
возрастанию в файл output.txt.
Формат входных данных Строка из английских букв, цифр и знаков препинания
Формат результата Последовательность целых чисел отсортированная по
возрастанию*/

#define MAX_INPUT_SIZE 1001
#define MAX_NUMBERS 500
const char *input_file = "input.txt";
const char *output_file = "output.txt";
//--------------------------------------------------
int compare(const void *a, const void *b);
//--------------------------------------------------
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
    int num_arr[MAX_NUMBERS] = {0};
    char ch = '\0';
    int num = 0, count = 0, flag = 0;

    while ((ch = fgetc(input)) != EOF && ch != '\n' && ch != '\r')
    {
        if (ch >= '0' && ch <= '9')
        {
            num = num * 10 + ch - '0';
            flag = 1;
        }
        else if (flag)
        {
            num_arr[count++] = num;
            flag = 0;
            num = 0;
        }
    }
    if (flag) num_arr[count++] = num; // Последнее число

    qsort(num_arr, count, sizeof(int), compare);

    for (int i = 0; i < count; i++)
        fprintf(output, "%d ", num_arr[i]);

    //---------------------
    fclose(input);
    fclose(output);

    return 0;
}

//-----------------------------------------------------
int compare(const void *a, const void *b)
{
    return (*(int *)a - *(int *)b);
}