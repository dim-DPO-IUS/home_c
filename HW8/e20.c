#include <inttypes.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>

/*Переставить цифры
Переставить цифры в числе так, что бы получилось максимальное число.
Формат входных данных: Одно целое не отрицательное число
Формат результата: Целое не отрицательное число*/

// Сколько цифр в числе
int8_t count_digit(int32_t n);

// Число в массив цифр
// Нуждается в предварительном выполнении ф-ии count_digit() для того, что бы передать массив нужного размера и сам размер
void number_to_digits(int8_t out[], int8_t size, int32_t n);

// Функция для сборки числа из масива цифр
int32_t digits_to_number(int8_t digits[], int8_t size);

// Своп
void swap(int8_t *a, int8_t *b);

// Сортировка пузырьком
// up_dn: направление сортировки: true: up, false: down.
// start: с какого индекса начинать сортировку
void bubble_sort(int8_t arr[], int8_t start, int8_t size, bool up_dn);

// Основная функция.
// Переставляет цифры в числе так, что бы получилось максимальное число
int32_t number_transform(int32_t n);

int main(void)
{
    int32_t n = 0;
    scanf("%d", &n);
    printf("%d\n", number_transform(n));
    return 0;
}

//----------------------------------------

int32_t number_transform(int32_t n)
{
    int8_t size = count_digit(n);
    int8_t out[size];
    number_to_digits(out, size, n);
    bubble_sort(out, 0, size, false);
    return digits_to_number(out, size);
}

int8_t count_digit(int32_t n)
{
    return n == 0 ? 1 : (int8_t)log10(n) + 1;
}

void number_to_digits(int8_t out[], int8_t size, int32_t n)
{
    for (int8_t i = size - 1; i >= 0; i--) {
        out[i] = n % 10;
        n /= 10;
    }
}

int32_t digits_to_number(int8_t digits[], int8_t size)
{
    int32_t num = 0;
    for (int8_t i = 0; i < size; i++)
        num = num * 10 + digits[i];
    return num;
}

void swap(int8_t *a, int8_t *b)
{
    int8_t tmp = *a;
    *a = *b;
    *b = tmp;
}

void bubble_sort(int8_t arr[], int8_t start, int8_t size, bool up_dn)
{
    bool swapped;
    for (int8_t i = start; i < size - 1; i++) {
        swapped = false;
        for (int8_t j = start; j < size + start - i - 1; j++) {
            if ((arr[j] > arr[j + 1]) == up_dn) {
                swap(&arr[j], &arr[j + 1]);
                swapped = true;
            }
        }
        if (!swapped)
            break;
    }
}