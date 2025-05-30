#include <inttypes.h>
#include <stdio.h>

/*Среднее арифметическое чисел
Ввести c клавиатуры массив из 5 элементов, найти среднее арифметическое всех элементов массива.
Формат входных данных: 5 целых не нулевых чисел через пробел
Формат результата: Одно число в формате "%.3f"*/

enum
{
    SIZE = 5 // Размер массива
};

// Ф-ия ввода массива с клавиатуры
void input_array(int32_t arr[], int32_t size);

// Ф-ия считает среднее массива
float calculate_average(int32_t arr[], int32_t size);

int main(void)
{
    int32_t arr[SIZE] = {0};
    input_array(arr, SIZE);
    printf("%.3f\n", calculate_average(arr, SIZE));
    return 0;
}

void input_array(int32_t arr[], int32_t size)
{
    for (int32_t i = 0; i < size; i++) {
        scanf("%d", &arr[i]);
    }
}

float calculate_average(int32_t arr[], int32_t size)
{
    int32_t sum = 0;
    for (int32_t i = 0; i < size; i++) {
        sum += arr[i];
    }
    return (float)sum / size;
}