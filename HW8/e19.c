#include <inttypes.h>
#include <math.h>
#include <stdio.h>

/*Цифры по порядку
Вывести в порядке следования цифры, входящие в десятичную запись натурального числа N.
Формат входных данных: Одно натуральное число N
Формат результата: Цифры через пробел*/

// Печать массива
void printr_array(int8_t arr[], int8_t size);

// Сколько цифр в числе
int8_t count_digit(int32_t n);

// Число в массив цифр
// Нуждается в предварительном выполнении ф-ии count_digit() для того, что бы передать массив нужного размера и сам размер
void number_to_digits(int8_t out[], int8_t size, int32_t n);

int main(void)
{
    int32_t n = 0;
    scanf("%d", &n);
    int8_t size = count_digit(n);
    int8_t out[size];
    number_to_digits(out, size, n);
    printr_array(out, size);
    return 0;
}

//----------------------------------------

void printr_array(int8_t arr[], int8_t size)
{
    for (int32_t i = 0; i < size; i++)
        printf("%d ", arr[i]);
    printf("\n");
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