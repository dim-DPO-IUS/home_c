#include <inttypes.h>
#include <stdio.h>

/*Инверсия половинок
Считать массив из 10 элементов и выполнить инверсию отдельно для 1-ой и 2-ой половин массива. Необходимо изменить считанный массив и напечатать его одним циклом.
Формат входных данных: 10 целых элементов массива через пробел.
Формат результата: 10 целых элементов массива через пробел.*/

enum
{
    SIZE = 10 // Размер массива
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
    revers_array_part(arr, SIZE, 2);
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
    for (int32_t i = 0; i < size; i++) {
        if (i < size / (part * 2)) {
            swap(&arr[i], &arr[size / 2 - 1 - i]);
            swap(&arr[size / 2 + i], &arr[size - 1 - i]);
        }
        printf("%d ", arr[i]);
    }
    printf("\n");
}


