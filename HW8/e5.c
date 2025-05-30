#include <inttypes.h>
#include <stdio.h>

/*Сумма положительных элементов
Считать массив из 10 элементов и посчитать сумму положительных элементов массива.
Формат входных данных: 10 целых чисел через пробел
Формат результата: Одно целое число - сумма положительных элементов массива*/

enum
{
    SIZE = 10
};

// Ф-ия ввода массива с клавиатуры
void input_array(int32_t arr[], int32_t size);
// Ф-ия считающая сумму положительных элементов массива
int32_t sum_positive_elements(int32_t arr[], int32_t size);

int main(void)
{
    int32_t arr[SIZE] = {0};
    input_array(arr, SIZE);
    printf("%d\n", sum_positive_elements(arr, SIZE));
    return 0;
}

void input_array(int32_t arr[], int32_t size)
{
    for (int8_t i = 0; i < size; i++) {
        scanf("%d", &arr[i]);
    }
}

int32_t sum_positive_elements(int32_t arr[], int32_t size)
{
    int32_t sum = 0;
    for (int32_t i = 0; i < size; i++) {
        arr[i] > 0 ? sum += arr[i] : sum;
    }
    return sum;
}
