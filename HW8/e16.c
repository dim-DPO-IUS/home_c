#include <inttypes.h>
#include <stdio.h>

/*Чаще других
Дан массив из 10 элементов. Определить, какое число в массиве встречается чаще всего. Гарантируется, что такое число ровно 1.
Формат входных данных: 10 целых числе через пробел
Формат результата: Одно число, которое встречается чаще других.*/

enum
{
    SIZE = 10 // Размер массива
};

// Ввод массива с клавиатуры
void input_array(int32_t arr[], int32_t size);

// Сколько раз встречается элемент elem
int32_t element_frequency(int32_t arr[], int32_t size, int32_t elem);

// Поиск элемента встречающегося чаще всего
int32_t find_most_frequent(int32_t arr[], int32_t size);

int main(void)
{
    int32_t arr[SIZE] = {0};
    input_array(arr, SIZE);
    printf("%d\n", find_most_frequent(arr, SIZE));
    return 0;
}

//----------------------------------------

void input_array(int32_t arr[], int32_t size)
{
    for (int32_t i = 0; i < size; i++) {
        scanf("%d", &arr[i]);
    }
}

int32_t element_frequency(int32_t arr[], int32_t size, int32_t elem)
{
    int32_t cnt_elem = 0;
    for (int32_t i = 0; i < size; i++)
        arr[i] == elem ? cnt_elem++ : cnt_elem;
    return cnt_elem;
}

int32_t find_most_frequent(int32_t arr[], int32_t size)
{
    int32_t most_freq = 0, count = 0;
    for (int32_t i = 0; i < size; i++) {
        int32_t cnt = element_frequency(arr, size, arr[i]);
        if (cnt > count) {
            count = cnt;
            most_freq = arr[i];
        }
    }
    return most_freq;
}
