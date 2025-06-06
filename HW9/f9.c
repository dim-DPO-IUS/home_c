#include <stdio.h>
/*Поменять местами
Составить только функцию которая в массиве находит максимальный из отрицательных
элементов и меняет его местами с последним элементом массива. Гарантируется, что
в массиве только один такой элемент или же такой элемент отсутствует. Если
отрицательных элементов нет - массив не менять. Прототип функции: 

void swap_negmax_last(int size, int a[])

Формат входных данных: Функция принимает на вход размер массива и указатель на
начало массива. Массив состоит из целых чисел.*/

enum
{
    SIZE = 10, // Размер массива
};

// Ввод массива с клавиатуры
void input_array(int arr[], int size);
//
void print_array(int arr[], int size);
//
void swap_negmax_last(int size, int a[]);

int main(void)
{
    int arr[SIZE] = {0};
    input_array(arr, SIZE);
    swap_negmax_last(SIZE, arr);
    print_array(arr, SIZE);
    return 0;
}

//----------------------------------------------------

void swap_negmax_last(int size, int a[])
{
    int max_neg = 0, inx = 0;
    for (int i = 0; i < size; i++)
    {
        if (a[i] < 0)
        {
            max_neg = a[i];
            inx = i;
            break;
        }
    }

    if (max_neg == 0) return;

    for (int i = 0; i < size; i++)
    {
        if (a[i] >= 0) continue;

        if (a[i] > max_neg)
        {
            max_neg = a[i];
            inx = i;
        }
    }

    a[inx] = a[size - 1];
    a[size - 1] = max_neg;
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
