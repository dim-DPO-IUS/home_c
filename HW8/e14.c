#include <inttypes.h>
#include <stdio.h>

/*Более одного раза
Считать массив из 10 элементов и выделить в другой массив все числа, которые встречаются более одного раза. В результирующем массиве эти числа не должны повторяться.
Формат входных данных: 10 целых чисел через пробел
Формат результата: Целые числа через пробел, которые встречаются более одного раза в исходном массиве.*/

enum
{
    SIZE = 10 // Размер массива
};

// Ввод массива с клавиатуры
void input_array(int32_t arr[], int32_t size);

// Печать массива
void printr_array(int32_t arr[], int32_t size);

// Поиск совпадений внутри массива
int32_t find_in_array(int32_t arr[], int32_t size, int32_t out[]);

// Поиск элемента внутри массива
// Вернет индекс последнего встреченного элемента elem или -1
int32_t find_elem(int32_t arr[], int32_t size, int32_t elem);

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
        for (int32_t j = i + 1; j < size; j++) {
            if (arr[i] == arr[j] && find_elem(out, count, arr[i]) < 0) {
                out[count] = arr[i];
                count++;
            }
        }
    }
    return count;
}

int32_t find_elem(int32_t arr[], int32_t size, int32_t elem)
{
    int32_t inx_elem = -1;
    for (int32_t i = 0; i < size; i++) {
        inx_elem = arr[i] == elem ? inx_elem = i : inx_elem;
    }
    return inx_elem;
}
