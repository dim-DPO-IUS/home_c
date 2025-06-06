#include <stdio.h>

/*В заданном интервале
Составить функцию которая возвращает количество элементов на заданном отрезке
[from, to] для массива. Прототип функции 

int count_between(int from, int to, int size, int a[])

Формат входных данных: функция принимает значения концов отрезка from и to,
размер массива, массив целых чисел.

Формат результата: функция возвращает целое число - количество числе в интервале
[from, to]*/

enum
{
    SIZE = 10,
    FROM = 4,
    TO = 6
};

void input_array(int arr[], int size);
void print_array(int arr[], int size);
int count_between(int from, int to, int size, int a[]);

// --------------------------------

int main(void)
{
    int arr[SIZE] = {0};
    input_array(arr, SIZE);
    printf("%d\n", count_between(FROM, TO, SIZE, arr));
    return 0;
}

// --------------------------------

int count_between(int from, int to, int size, int a[])
{
    int count = 0;
    for (int i = 0; i < size; i++)
    {
        if (a[i] >= from && a[i] <= to)
        {
            count++;
        }
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