#include <inttypes.h>
#include <stdio.h>

/*Два максимума
Считать массив из 10 элементов и найти в нем два максимальных элемента и напечатать их сумму.
Формат входных данных: 10 целых чисел через пробел.
Формат результата: Сумма двух максимальных элементов.*/

enum
{
    SIZE = 10
};

// Ф-ия ввода массива с клавиатуры
void input_array(int32_t arr[], int32_t size);

// Ф-ия поиска индекса максимума массива. Из поиска исключается элемент[exc_inx]
// inx_max: искомый индекс максимум
// exc_inx: этот индекс игнорируется при поиске. exc_inx: -1 не игнорировать индексы.
void find_max_index(int32_t arr[], int32_t size, int32_t *inx_max, int32_t exc_inx);

int main(void)
{
    int32_t arr[SIZE] = {0};
    input_array(arr, SIZE);
    int32_t inx_max1 = 0, inx_max2 = 0;
    find_max_index(arr, SIZE, &inx_max1, -1);
    find_max_index(arr, SIZE, &inx_max2, inx_max1);
    printf("%d\n", arr[inx_max1] + arr[inx_max2]);
    return 0;
}

void find_max_index(int32_t arr[], int32_t size, int32_t *inx_max, int32_t exc_inx)
{
    int32_t max = 0;
    if (exc_inx == 0) {
        max = arr[1];
        *inx_max = 1;
    } else {
        max = arr[0];
        *inx_max = 0;
    }

    for (int32_t i = 0; i < size; i++) {
        if (i == exc_inx)
            continue;
        if (arr[i] > max) {
            *inx_max = i;
            max = arr[i];
        }
    }
}

void input_array(int32_t arr[], int32_t size)
{
    for (int8_t i = 0; i < size; i++) {
        scanf("%d", &arr[i]);
    }
}

