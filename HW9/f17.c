#include <math.h>
#include <stdio.h>

/*След матрицы
Составить функцию которая находит след матрицы в двумерном массиве.
Показать пример ее работы на матрице из 5 на 5 элементов. След матрицы -
это сумма элементов на главной диагонали.

Формат входных данных: 25 целых чисел через пробел.
Формат результата: одно целое число.*/

enum
{
    SIZE = 25
};

void input_array(int arr[], int size);
int matrix_trace(int arr[]);
// --------------------------------

int main(void)
{
    int arr[SIZE] = {0};
    input_array(arr, SIZE);
    printf("%d\n", matrix_trace(arr));
    return 0;
}

// --------------------------------

int matrix_trace(int arr[])
{
    int sum = 0;
    int step = sqrt(SIZE) + 1;
    for (int i = 0; i < SIZE; i += step)
    {
        sum += arr[i];
    }
    return sum;
}

void input_array(int arr[], int size)
{
    for (int i = 0; i < size; i++)
    {
        scanf("%d", &arr[i]);
    }
}
