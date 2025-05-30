#include <inttypes.h>
#include <stdbool.h> // Для типа bool
#include <stdio.h>

/*Положительные и отрицательные
Считать 10 чисел в диапазоне от -500 до 500 и разложить по двум массивам: в одни помещать только положительные, во второй - только отрицательные. Числа, равные нулю, игнорировать. Вывести на экран все элементы обоих массивов.
Формат входных данных: 10 целых чисел через пробел.
Формат результата: Сперва положительные числа, потом отрицательыне числа, через пробел.*/

enum
{
    SIZE = 10 // Размер массива
};

// Ввод массива с клавиатуры
void input_array(int32_t arr[], int32_t size);

// Печать массива
void printr_array(int32_t arr[], int32_t size);

// Поиск внутри массива положительных или отрицательных значений
// sign: знак искомого элемента: true: +, false: -.
int32_t find_in_array(int32_t arr[], int32_t size, int32_t out[], bool sign);

int main(void)
{
    int32_t arr[SIZE] = {0};
    int32_t out[SIZE] = {0};
    int32_t count = 0;

    input_array(arr, SIZE);
    
    count = find_in_array(arr, SIZE, out, true);
    printr_array(out, count);

    count = find_in_array(arr, SIZE, out, false);
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
    // printf("\n");
}

int32_t find_in_array(int32_t arr[], int32_t size, int32_t out[], bool sign)
{
    int32_t count = 0;
    for (int32_t i = 0; i < size; i++) {
        if ((arr[i] > 0) == sign && arr[i] != 0) {
            out[count] = arr[i];
            count++;
        }
    }
    return count;
}
