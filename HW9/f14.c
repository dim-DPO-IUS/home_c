#include <stdio.h>

/*Сумма в интервале
Составить функцию которая возвращает сумму элементов в заданном отрезке [from,
to] для массива. Прототип функции 

int sum_between_ab(int from, int to, int size, int a[])

Формат входных данных: функция принимает концы отрезка from и to, размер
массива, массив целых чисел.
Формат результата: функция возвращает сумму элементов в интервале [from, to]*/

enum
{
    SIZE = 10,
    FROM = 4,
    TO = 6
};

void input_array(int arr[], int size);
void print_array(int arr[], int size);
int sum_between_ab(int from, int to, int size, int a[]);

// --------------------------------

int main(void)
{
    int arr[SIZE] = {0};
    input_array(arr, SIZE);
    printf("%d\n", sum_between_ab(FROM, TO, SIZE, arr));
    return 0;
}

// --------------------------------

int sum_between_ab(int from, int to, int size, int a[])
{
    int sum = 0;
    for (int i = 0; i < size; i++)
    {
        if (a[i] >= from && a[i] <= to || a[i] <= from && a[i] >= to)
        {
            sum += a[i];
        }
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

void print_array(int arr[], int size)
{
    for (int i = 0; i < size; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
}