#include <inttypes.h>
#include <stdio.h>

/*Циклический сдвиг массива вправо на 4
Считать массив из 12 элементов и выполнить циклический сдвиг ВПРАВО на 4 элемента.
Формат входных данных: 12 целых чисел через пробел
Формат результата: 12 целых чисел через пробел*/

enum
{
    SIZE = 12 // Размер массива
    ,
    N = 4 // сдвиг
};

// Ввод массива с клавиатуры
void input_array(int32_t arr[], int32_t size);

// Циклический сдвиг массива вправо
void shift_array_right(int32_t arr[], int32_t size);

// Циклический сдвиг массива вправо на N элементов
void shift_array_right_n(int32_t arr[], int32_t size, int32_t n);

// Печать массива
void printr_array(int32_t arr[], int32_t size);

int main(void)
{
    int32_t arr[SIZE] = {0};
    input_array(arr, SIZE);
    shift_array_right_n(arr, SIZE, N);
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

void shift_array_right_n(int32_t arr[], int32_t size, int32_t n)
{
    for (int32_t i = 0; i < n; i++) {
        shift_array_right(arr, size);
    }
}

void printr_array(int32_t arr[], int32_t size)
{
    for (int32_t i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}
