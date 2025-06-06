#include <stdbool.h>
#include <stdio.h>
/*Сортировка по взрастанию
Написать только одну функцию, которая сортирует массив по возрастанию.
Необходимо реализовать только одну функцию, всю программу составлять не надо.
Строго согласно прототипу. Имя функции и все аргументы должны быть: 

void sort_array(int size, int a[]).

Формат входных данных: Функция принимает на вход, первый аргумент - размер
массива, второй аргумент - адрес нулевого элемента. Формат результата: Функция
ничего не возвращает. Производит сортировку переданного ей массива по
возрастанию.*/

enum
{
    SIZE = 20 // Размер массива
};

// Ввод массива с клавиатуры
void input_array(int arr[], int size);

// Сортировка
void sort_array(int size, int a[]);

// Печать массива
void printr_array(int arr[], int size);

int main(void)
{
    int arr[SIZE] = {0};
    input_array(arr, SIZE);
    sort_array(SIZE, arr);
    printr_array(arr, SIZE);
    return 0;
}

// ----------------------------------------

void input_array(int arr[], int size)
{
    for (int i = 0; i < size; i++)
    {
        scanf("%d", &arr[i]);
    }
}

void printr_array(int arr[], int size)
{
    for (int i = 0; i < size; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

void sort_array(int size, int a[])
{
    bool swapped;
    for (int i = 0; i < size - 1; i++)
    {
        swapped = false;
        for (int *ptr = a; ptr < a + size - i - 1; ptr++)
        {
            if (*ptr > *(ptr + 1))
            {
                int tmp = *ptr;
                *ptr = *(ptr + 1);
                *(ptr + 1) = tmp;
                swapped = true;
            }
        }
        if (!swapped) break;
    }
}
