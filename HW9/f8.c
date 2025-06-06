#include <stdio.h>

/*Пропущенное число
Написать функцию и программу, демонстрирующую работу данной функции.
В последовательности записаны целые числа от M до N ( M < N, M >= 1) в
произвольном порядке, но одно из чисел пропущено (остальные встречаются ровно по
одному разу). N не превосходит 1000. Последовательность заканчивается числом 0.
Определить пропущенное число.*/

enum
{
    SIZE = 1000, 
};

int input_array(int arr[], int size);
void bubble_sort(int arr[], int n);
int find_number(int arr[], int size);

int main(void)
{
    int arr[SIZE] = {0};
    int inx_end = input_array(arr, SIZE);
    printf("%d ", find_number(arr, inx_end));
    return 0;
}

// ---------------------------------------------

int find_number(int arr[], int size)
{
    bubble_sort(arr, size);

    int i = 0;
    for (i = 0; i < size - 1; i++)
    {
        if (arr[i + 1] - arr[i] > 1)
        {
            break;
        }
    }

    return arr[i] + 1;
}

void bubble_sort(int arr[], int size)
{
    for (int i = 0; i < size - 1; i++)
    {
        for (int j = 0; j < size - i - 1; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

int input_array(int arr[], int size)
{
    int i = 0;
    for (i = 0; i < size; i++)
    {
        scanf("%d", &arr[i]);
        if (arr[i] == 0) break;
    }
    return i;
}
