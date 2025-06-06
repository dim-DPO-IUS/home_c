#include <stdio.h>

/*Сумма минимальна
Дан целочисленный массив из 30 элементов. Элементы массива могут принимать
произвольные целые значения помещающиеся в int. Необходимо создать функцию,
которая находит и выводит в порядке возрастания номера двух элементов массива,
сумма которых минимальна.
Формат входных данных: Последовательность из 30 целых
чисел через пробел.
Формат результата: Два целых числа через пробел.*/

enum
{
    SIZE = 30
};

void input_array(int arr[], int size);
void find_min_sum_pair(int arr[], int size);

// --------------------------------

int main(void)
{
    int arr[SIZE];
    input_array(arr, SIZE);
    find_min_sum_pair(arr, SIZE);
    return 0;
}

// --------------------------------

void find_min_sum_pair(int arr[], int size)
{
    int min_i = 0, min_j = 1;
    int min_sum = arr[0] + arr[1];

    for (int i = 0; i < size - 1; i++)
    {
        for (int j = i + 1; j < size; j++)
        {
            int current_sum = arr[i] + arr[j];
            if (current_sum < min_sum)
            {
                min_sum = current_sum;
                min_i = i;
                min_j = j;
            }
        }
    }

    printf("%d %d\n", min_i, min_j);
}

void input_array(int arr[], int size)
{
    for (int i = 0; i < size; i++)
    {
        scanf("%d", &arr[i]);
    }
}