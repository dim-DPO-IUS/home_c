#include <stdio.h>

/*Массив максимумов
Дана целочисленная квадратная матрица 10 х 10. реализовать алгоритм
вычисления суммы максимальных элементов из каждой строки. Напечатать
значение этой суммы. Предполагается, что в каждой строке такой элемент
единственный. Реализовать функцию поиска максимума в строке из 10 элементов

Формат входных данных: 10 строк состоящих из 10 целых чисел через пробел.

Формат результата: одно целое число*/

enum
{
    SIZE = 10
};

void input_matrix(int *matrix, int rows, int cols);
int sum_max_matrix(int *matrix, int rows, int cols);

// --------------------------------

int main(void)
{
    int mat[SIZE][SIZE];
    input_matrix(&mat[0][0], SIZE, SIZE);
    int sum = sum_max_matrix(&mat[0][0], SIZE, SIZE);
    printf("%d\n", sum);
    return 0;
}

// --------------------------------

int sum_max_matrix(int *matrix, int rows, int cols)
{
    int sum = 0;
    for (int i = 0; i < rows; i++)
    {
        int max = matrix[i * cols];
        for (int j = 0; j < cols; j++)
        {
            if (matrix[i * cols + j] > max)
            {
                max = matrix[i * cols + j];
            }
        }
        sum += max;
    }
    return sum;
}

void input_matrix(int *matrix, int rows, int cols)
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            scanf("%d", &matrix[i * cols + j]);
        }
    }
}

