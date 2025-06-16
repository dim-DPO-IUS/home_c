#include <stdio.h>

/*Равносторонние треугольники
Cia очень любит равносторонние треугольники. Он все время выкладывает их из
камней. Ling дал Cia камни и попросил его составить такой треугольник если это
возможно. Помогите Cia сложить треугольник используя все камни или напечатайте
слов NO, если это невозможно. Пример треугольников, которые составляет Cia:
 *
* *

  *
 * *
* * *

   *
  * *
 * * *
* * * *
Во входном файле input.txt записано некоторое количество символов * (камней).
Необходимо построить равносторонний треугольник используя все символы * и символ
пробел, записать ответ в выходной файл output.txt. Между соседними
символами * строго один пробел. Если треугольник невозможно составить, используя
все камни, то необходимо записать единственное слово NO в файл output.txt.*/

#define MAX 1001
const char *input_file = "input.txt";
const char *output_file = "output.txt";
// Проверка возможности построения треугольника
int is_triangular_number(int n);
// Рисование треугольника
void print_triangle(int levels, FILE *output);

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
    int star_count = 0;
    int c;

    // Подсчет звездочек
    while ((c = fgetc(input)) != EOF)
        if (c == '*') star_count++;

    fclose(input);

    int levels = is_triangular_number(star_count);

    if (levels < 0)
        fprintf(output, "NO");
    else
    {
        print_triangle(levels, output);
    }
    //---------------------------

    fclose(output);
    return 0;
}

//-----------------------------------------------------
// Является ли число n треугольным.
// Если да, то вернет положительное число
// Если нет, то вернет отрицательное число
// Положительное возвращенное число - число уровней у треугольника
int is_triangular_number(int n)
{
    int k = 1;
    while (k * (k + 1) / 2 < n)
    {
        k++;
    }
    return k * (k + 1) / 2 == n ? k : -k;
}

void print_triangle(int levels, FILE *output)
{
    for (int i = 1; i <= levels; i++)
    {
        // Пробелы перед первой звездой для центрирования
        for (int j = 0; j < levels - i; j++)
        {
            fprintf(output, " ");
        }
        // Вывод звезд с пробелами
        for (int j = 0; j < i; j++)
        {
            fprintf(output, "*");
            if (j < i - 1)
            {
                fprintf(output, " ");
            }
        }
        fprintf(output, "\n");
    }
}