#include <inttypes.h>
#include <stdbool.h> // Для типа bool
#include <stdio.h>

/*Отсортировать по последней цифре
Считать массив из 10 элементов и отсортировать его по последней цифре.
Формат входных данных: 10 целых чисел через пробел
Формат результата: Этот же массив отсортированный по последней цифре */

enum
{
    SIZE = 10 // Размер массива
};

// Ввод массива с клавиатуры
void input_array(int32_t arr[], int32_t size);

// Своп
void swap(int32_t *a, int32_t *b);

// Сортировка пузырьком по последней цифре элементов
void bubble_sort_last_num(int arr[], int size);

// Печать массива
void printr_array(int32_t arr[], int32_t size);

int main(void)
{
    int32_t arr[SIZE] = {0};
    input_array(arr, SIZE);
    bubble_sort_last_num(arr, SIZE);
    printr_array(arr, SIZE);
    return 0;
}

//----------------------------------------

void input_array(int32_t arr[], int32_t size)
{
    for (int32_t i = 0; i < size; i++) {
        scanf("%d", &arr[i]);
    }
}

void printr_array(int32_t arr[], int32_t size)
{
    for (int32_t i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

void swap(int32_t *a, int32_t *b)
{
    int32_t tmp = *a;
    *a = *b;
    *b = tmp;
}

void bubble_sort_last_num(int arr[], int size)
{
    bool swapped;
    for (int i = 0; i < size - 1; i++) {
        swapped = false;
        for (int j = 0; j < size - i - 1; j++) {
            if (arr[j]%10 > arr[j + 1]%10) {
                swap(&arr[j], &arr[j + 1]);
                swapped = true;
            }
        }
        if (!swapped)
            break;
    }
}
