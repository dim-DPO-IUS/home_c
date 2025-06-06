#include <stdio.h>
#include <stdlib.h>

/*Больше по модулю
Составить функцию которая определяет в массиве, состоящем из положительных и
отрицательных чисел, сколько элементов превосходят по модулю максимальный
элемент. Прототип функции 

int count_bigger_abs(int n, int a[]);

Формат входных данных: функция получает размер массива и массив целых чисел.
Формат результата: функция возвращает целое число раное количеству элементов
превосходящих по модулю максимальный элемент.*/

enum
{
    SIZE = 10
};

void input_array(int arr[], int size);
void print_array(int arr[], int size);
int count_bigger_abs(int n, int a[]);

// --------------------------------

int main(void)
{
    int arr[SIZE] = {0};
    input_array(arr, SIZE);
    printf("%d\n", count_bigger_abs(SIZE, arr));
    return 0;
}

// --------------------------------

int count_bigger_abs(int n, int a[])
{

    int max = a[0];
    for (int i = 1; i < n; i++)
    {
        if (a[i] > max) max = a[i];
    }

    int count = 0;
    for (int i = 0; i < n; i++)
    {
        if (-a[i] > max) count++;
    }

    return count;
}

void input_array(int arr[], int size)
{
    for (int i = 0; i < size; i++)
    {
        scanf("%d", &arr[i]);
    }
}

void print_array(int arr[], int size)
{
    for (int i = 0; i < size; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
}