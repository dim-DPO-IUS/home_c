#include <inttypes.h>
#include <stdio.h>

/*Циклический сдвиг массива вправо
Считать массив из 10 элементов и выполнить циклический сдвиг ВПРАВО на 1.
Формат входных данных: 10 целых чисел через пробел
Формат результата: 10 целых чисел через пробел сдвинутых вправо на 1 элемент циклически*/

enum
{
    SIZE = 10 // Размер массива
};

// Ввод массива с клавиатуры
void input_array(int32_t arr[], int32_t size);

// Циклический сдвиг массива вправо
void shift_array_right(int32_t arr[], int32_t size);

// Печать массива
void printr_array(int32_t arr[], int32_t size);

int main(void)
{
    int32_t arr[SIZE] = {0};
    input_array(arr, SIZE);
    shift_array_right(arr, SIZE);
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

void shift_array_right(int32_t arr[], int32_t size)
{
    int32_t tmp = arr[size - 1];
    for (int32_t i = size - 1; i >= 0; i--) {
        arr[i] = arr[i - 1];
    }
    arr[0] = tmp;
}

void printr_array(int32_t arr[], int32_t size)
{
    for (int32_t i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}