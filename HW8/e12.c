#include <inttypes.h>
#include <stdbool.h> // Для типа bool
#include <stdio.h>

/*По убыванию и по возрастанию
Считать массив из 10 элементов и отсортировать первую половину по возрастанию, а вторую – по убыванию.
Формат входных данных: 10 целых чисел через пробел
Формат результата: Исходный массив. Первая часть отсортирована по возрастанию, вторая половина по убыванию.*/

enum
{
    SIZE = 10 // Размер массива
};

// Ввод массива с клавиатуры
void input_array(int32_t arr[], int32_t size);

// Своп
void swap(int32_t *a, int32_t *b);

// Сортировка пузырьком
// up_dn: направление сортировки: true: up, false: down.
// start: с какого индекса начинать сортировку
void bubble_sort(int32_t arr[], int32_t start, int32_t size, bool up_dn);

// Печать массива
void printr_array(int32_t arr[], int32_t size);

int main(void)
{
    int32_t arr[SIZE] = {0};
    input_array(arr, SIZE);
    bubble_sort(arr, 0, SIZE / 2, true);
    bubble_sort(arr, SIZE / 2, SIZE, false);
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

void bubble_sort(int32_t arr[], int32_t start, int32_t size, bool up_dn)
{
    bool swapped;
    for (int32_t i = start; i < size - 1; i++) {
        swapped = false;
        for (int32_t j = start; j < size + start - i - 1; j++) {
            if ((arr[j] > arr[j + 1]) == up_dn) {
                swap(&arr[j], &arr[j + 1]);
                swapped = true;
            }
        }
        if (!swapped)
            break;
    }
}

