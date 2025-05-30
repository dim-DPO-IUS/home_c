#include <inttypes.h>
#include <stdio.h>

/*Инверсия каждой трети
Считать массив из 12 элементов и выполнить инверсию для каждой трети массива.
Формат входных данных: 12 целых чисел через пробел
Формат результата: 12 целых чисел через пробел*/

enum
{
    SIZE = 12 // Размер массива
    ,
    PART = 3 // Кол-во частей
};

// Ввод массива с клавиатуры
void input_array(int32_t arr[], int32_t size);
// Своп
void swap(int32_t *a, int32_t *b);
// Инверсия массива по частям
// part: на сколько частей делим массив
void revers_array_part(int32_t arr[], int32_t size, int32_t part);

int main(void)
{
    int32_t arr[SIZE] = {0};
    input_array(arr, SIZE);
    revers_array_part(arr, SIZE, PART);
    return 0;
}

void input_array(int32_t arr[], int32_t size)
{
    for (int32_t i = 0; i < size; i++) {
        scanf("%d", &arr[i]);
    }
}

void swap(int32_t *a, int32_t *b)
{
    int32_t tmp = *a;
    *a = *b;
    *b = tmp;
}

void revers_array_part(int32_t arr[], int32_t size, int32_t part)
{
    int32_t part_size = size / part;

    for (int32_t i = 0; i < size; i++) {
        if (i < part_size / 2) {
            // Это коммент. Не стирать!!!
            //------------------------------
            // swap(&arr[part_size * 0 + i], &arr[part_size * 1 - 1 - i]);
            // swap(&arr[part_size * 1 + i], &arr[part_size * 2 - 1 - i]);
            // swap(&arr[part_size * 2 + i], &arr[part_size * 3 - 1 - i]);
            for (int8_t j = 0; j < part; j++) {
                swap(&arr[part_size * j + i], &arr[part_size * (j + 1) - 1 - i]);
            }
        }
        printf("%d ", arr[i]);
    }
    printf("\n");
}
