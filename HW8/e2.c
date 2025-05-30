#include <inttypes.h>
#include <stdio.h>

/*Найти минимум
Ввести c клавиатуры массив из 5 элементов, найти минимальный из них.
Формат входных данных: 5 целых чисел через пробел
Формат результата: Одно единственное целое число*/

enum
{
    SIZE = 5
};

// Ф-ия ввода массива с клавиатуры
void input_array(int32_t arr[], int32_t size);

// Ф-ия поиска минимума массива
int32_t find_min_array(int32_t arr[], int32_t size);

int main(void)
{
    int32_t arr[SIZE] = {0};
    input_array(arr, SIZE);
    printf("%d\n", find_min_array(arr, SIZE));
    return 0;
}

void input_array(int32_t arr[], int32_t size)
{
    for (int8_t i = 0; i < size; i++) {
        scanf("%d", &arr[i]);
    }
}

int32_t find_min_array(int32_t arr[], int32_t size)
{
    int32_t min = arr[0];

    for (int32_t i = 1; i < size; i++) {
        arr[i] < min ? min = arr[i] : min;
    }
    return min;
}
