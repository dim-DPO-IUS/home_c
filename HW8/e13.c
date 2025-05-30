#include <inttypes.h>
#include <stdio.h>

/*Вторая с конца ноль
Считать массив из 10 элементов и отобрать в другой массив все числа, у которых вторая с конца цифра (число десятков) – ноль.
Формат входных данных: 10 целых чисел через пробел.
Формат результата: Целые числа через пробел, у котороых вторая с конца цифра - ноль*/

enum
{
    SIZE = 10 // Размер массива
};

// Ввод массива с клавиатуры
void input_array(int32_t arr[], int32_t size);

// Печать массива
void printr_array(int32_t arr[], int32_t size);

// Поиск внутри массива
int32_t find_in_array(int32_t arr[], int32_t size, int32_t out[]);

int main(void)
{
    int32_t arr[SIZE] = {0};
    int32_t out[SIZE] = {0};

    input_array(arr, SIZE);
    int32_t count = find_in_array(arr, SIZE, out);
    printr_array(out, count);
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

int32_t find_in_array(int32_t arr[], int32_t size, int32_t out[])
{
    int32_t count = 0;
    for (int32_t i = 0; i < size; i++) {
        if ((arr[i] / 10) % 10 == 0) {
            out[count] = arr[i];
            count++;
        }
    }
    return count;
}
