#include <stdio.h>
/*Два одинаковых
Написать только одну логическую функцию, которая определяет, верно ли, что среди
элементов массива есть два одинаковых. Если ответ «да», функция возвращает 1;
если ответ «нет», то 0. Строго согласно прототипу:

int is_two_same(int size, int a[]);

Формат входных данных: Массив из целых чисел
Формат результата: Функция возвращает 1 или 0*/

enum
{
    SIZE = 10
};

// Ввод массива с клавиатуры
void input_array(int arr[], int size);

int is_two_same(int size, int a[]);

int main(void)
{
    int arr[SIZE] = {0};
    input_array(arr, SIZE);
    printf("%d\n", is_two_same(SIZE, arr));
    return 0;
}

//------------------------------------

void input_array(int arr[], int size)
{
    for (int i = 0; i < size; i++)
    {
        scanf("%d", &arr[i]);
    }
}

int is_two_same(int size, int a[])
{
    int yes_no = 0;
    for (int i = 0; i < size; i++)
    {
        for (int j = i + 1; j < size; j++)
        {
            if (a[j] == a[i])
            {
                yes_no = 1;
                break;
            }
        }
    }
    return yes_no;
}
