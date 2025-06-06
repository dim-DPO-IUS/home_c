#include <stdio.h>

/*Четные и нечетные
Дан целочисленный массив из 10 элементов. Необходимо определить количество
четных и нечетных чисел. Если количество чётных чисел больше, чем количество
нечётных, заменить каждое нечетное число на произведение нечетных цифр в его
десятичной записи. Если количество нечётных чисел больше или равно количеству
чётных, заменить каждое чётное число на произведение чётных цифр в его
десятичной записи.
Формат входных данных: 10 целых чисел через пробел
Формат результата: 10 целых чисел через пробел*/

enum
{
    SIZE = 10
};

void input_array(int arr[], int size);
void print_array(int arr[], int size);
// Функция для вычисления произведения нечетных цифр числа
int prod_odd_digits(int num);
// Функция для вычисления произведения четных цифр числа
int prod_even_digits(int num);
// Итоговая функция
void transform_arr(int arr[], int size);
// --------------------------------

int main(void)
{
    int arr[SIZE] = {0};
    input_array(arr, SIZE);
    transform_arr(arr, SIZE);
    print_array(arr, SIZE);
    return 0;
}

// --------------------------------
void transform_arr(int arr[], int size)
{
    int even_count = 0, odd_count = 0;

    for (int i = 0; i < size; i++)
    {
        arr[i] % 2 ? odd_count++ : even_count++;
    }

    if (even_count > odd_count)
    {
        for (int i = 0; i < size; i++)
        {
            if (arr[i] % 2 != 0)
            {
                arr[i] = prod_odd_digits(arr[i]);
            }
        }
    }
    else
    {
        for (int i = 0; i < size; i++)
        {
            if (arr[i] % 2 == 0)
            {
                arr[i] = prod_even_digits(arr[i]);
            }
        }
    }
}

int prod_odd_digits(int num)
{
    num = num < 0 ? -num : num;
    int product = 1;
    while (num > 0)
    {
        int digit = num % 10;
        if (digit % 2 != 0)
        {
            product *= digit;
        }
        num /= 10;
    }
    return product;
}

int prod_even_digits(int num)
{
    num = num < 0 ? -num : num;
    int product = 1;
    while (num > 0)
    {
        int digit = num % 10;
        if (digit % 2 == 0)
        {
            product *= digit;
        }
        num /= 10;
    }
    return product;
}

void input_array(int arr[], int size)
{
    for (int i = 0; i < size; i++)
    {
        scanf("%d", &arr[i]);
    }
}

void print_array(int arr[], int size)
{
    for (int i = 0; i < size; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
}
