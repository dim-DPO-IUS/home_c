
#include <stdio.h>

/*Максимум в массиве
Написать только одну функцию, которая находит максимальный элемент в массиве.
Всю программу загружать не надо.

Прототип функции: int find_max_array(int size, int a[])

Формат входных данных: Массив состоящий из целых чисел. Первый аргумент, размер
массива, второй аргумент адрес нулевого элемента. Формат результата: Одно целое
число*/

enum
{
    SIZE = 10
};

// Ввод массива с клавиатуры
void input_array(int arr[], int size);

int find_max_array(int size, int a[]);

int main(void)
{
    int arr[SIZE] = {0};
    input_array(arr, SIZE);
    printf("%d\n", find_max_array(SIZE, arr));
    return 0;
}

//------------------------------------

int find_max_array(int size, int a[])
{
    int max = a[0];
    for (int i = 1; i < size; i++)
    {
        a[i] > max ? max = a[i] : max;
    }
    return max;
}

void input_array(int arr[], int size)
{
    for (int i = 0; i < size; i++)
    {
        scanf("%d", &arr[i]);
    }
}