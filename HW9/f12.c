#include <stdio.h>

/*Поменять местами
Составить функцию которая меняет в массиве минимальный и максимальный элемент
местами. Прототип функции 

void change_max_min(int size, int a[])

Формат входных данных: Функция принимает на вход размер массива и массив чисел
типа int.
Формат результата: Функция не возвращает значения, измененный массив
сохраняется на месте исходного.*/

enum
{
    SIZE = 10
};

void input_array(int arr[], int size);
void print_array(int arr[], int size);
void change_max_min(int size, int a[]);

// --------------------------------

int main(void)
{
    int arr[SIZE] = {0};
    input_array(arr, SIZE);
    change_max_min(SIZE, arr);
    print_array(arr, SIZE);
    return 0;
}

// --------------------------------

void change_max_min(int size, int a[])
{
    if (size <= 1) return;

    int min_index = 0, max_index = 0;
    int min_val = a[0], max_val = a[0];

    for (int i = 1; i < size; i++)
    {
        if (a[i] < min_val)
        {
            min_val = a[i];
            min_index = i;
        }
        if (a[i] > max_val)
        {
            max_val = a[i];
            max_index = i;
        }
    }

    int temp = a[min_index];
    a[min_index] = a[max_index];
    a[max_index] = temp;
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