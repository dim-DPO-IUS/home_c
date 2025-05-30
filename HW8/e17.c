#include <inttypes.h>
#include <stdio.h>

/*Только один раз
Дан массив из 10 элементов. В массиве найти элементы, которые в нем встречаются только один раз, и вывести их на экран.
Формат входных данных: 10 целых чисел через пробел
Формат результата: Элементы которые встречаются только один раз через пробел*/

enum
{
    SIZE = 10 // Размер массива
};

// Ввод массива с клавиатуры
void input_array(int32_t arr[], int32_t size);

// Печать массива
void printr_array(int32_t arr[], int32_t size);

// Сколько раз встречается элемент elem
int32_t element_frequency(int32_t arr[], int32_t size, int32_t elem);

// Поиск всех элементов, встречающихся один раз
int32_t find_unique_elements(int32_t arr[], int32_t size, int32_t out[]);

int main(void)
{
    int32_t arr[SIZE] = {0};
    int32_t out[SIZE] = {0};
    input_array(arr, SIZE);
    int32_t count = find_unique_elements(arr, SIZE, out);
    printr_array(out, count);
    return 0;
}

//----------------------------------------

void input_array(int32_t arr[], int32_t size)
{
    for (int32_t i = 0; i < size; i++)
        scanf("%d", &arr[i]);
}

void printr_array(int32_t arr[], int32_t size)
{
    for (int32_t i = 0; i < size; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

int32_t element_frequency(int32_t arr[], int32_t size, int32_t elem)
{
    int32_t cnt_elem = 0;
    for (int32_t i = 0; i < size; i++)
        arr[i] == elem ? cnt_elem++ : cnt_elem;
    return cnt_elem;
}

int32_t find_unique_elements(int32_t arr[], int32_t size, int32_t out[])
{
    int32_t count = 0;
    for (size_t i = 0; i < size; i++)
        if (element_frequency(arr, size, arr[i]) == 1)
            out[count++] = arr[i];
    return count;
}
