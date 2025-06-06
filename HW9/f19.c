#include <stdio.h>

/*Больше среднего
Определить количество положительных элементов квадратной матрицы, превышающих по
величине среднее арифметическое всех элементов главной диагонали. Реализовать
функцию среднее арифметическое главной диагонали.
Формат входных данных: 5 строк по 5 целых чисел через пробел
Формат результата: одно целое число*/

enum
{
    SIZE = 5
};

void input_matrix(int *matrix, int rows, int cols);
int avg_main_diagonal(int *matrix, int rows, int cols);

// --------------------------------

int main(void)
{
    int mat[SIZE][SIZE];
    input_matrix(&mat[0][0], SIZE, SIZE);
    int avg = avg_main_diagonal(&mat[0][0], SIZE, SIZE);
    printf("%d\n", avg);
    return 0;
}

// --------------------------------

int avg_main_diagonal(int *matrix, int rows, int cols)
{
    int sum = 0;
    int inx_line = rows * cols;
    int step = cols + 1;
    for (int i = 0; i < inx_line; i += step)
    {
        sum += matrix[i];
    }
    int avg = sum / rows;
    int count = 0;
    for (int i = 0; i < inx_line; i++)
    {
        matrix[i] > avg ? count++ : count;
    }
    return count;
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
