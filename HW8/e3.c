#include <inttypes.h>
#include <stdio.h>

/*Максимум и минимум
Считать массив из 10 элементов и найти в нем максимальный и минимальный элементы и их номера.
Формат входных данных: 10 целых чисел через пробел
Формат результата: 4 целых числа через пробел: номер максимума, максимум, номер минимума, минимум.*/

enum
{
    SIZE = 10
};

// Ф-ия ввода массива с клавиатуры
void input_array(int32_t arr[], int32_t size);

// Ф-ия поиска индекса максимума массива
void find_inx_max_array(int32_t arr[], int32_t size, int32_t *inx_max);

// Ф-ия поиска индекса минимума массива
void find_inx_min_array(int32_t arr[], int32_t size, int32_t *inx_min);

int main(void)
{
    int32_t arr[SIZE] = {0};
    int32_t inx_min = 0, inx_max = 0;
    input_array(arr, SIZE);
    find_inx_max_array(arr, SIZE, &inx_max);
    find_inx_min_array(arr, SIZE, &inx_min);
    printf("%d %d %d %d\n", inx_max + 1, arr[inx_max], inx_min + 1, arr[inx_min]);
    return 0;
}

void input_array(int32_t arr[], int32_t size)
{
    for (int8_t i = 0; i < size; i++) {
        scanf("%d", &arr[i]);
    }
}

void find_inx_max_array(int32_t arr[], int32_t size, int32_t *inx_max)
{
    int32_t max = arr[0];

    for (int32_t i = 1; i < size; i++) {
        if (arr[i] > max) {
            *inx_max = i;
            max = arr[i];
        }
    }
}

void find_inx_min_array(int32_t arr[], int32_t size, int32_t *inx_min)
{
    int32_t min = arr[0], max = arr[0];

    for (int32_t i = 1; i < size; i++) {
        if (arr[i] < min) {
            *inx_min = i;
            min = arr[i];
        }
    }
}