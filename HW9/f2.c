#include <stdio.h>
/*Четные в начало
Написать только одну функцию, которая ставит в начало массива все четные элементы, а в конец – все нечетные. Не нарушайте порядок следования чисел между собой. Строго согласно прототипу:

void sort_even_odd(int n, int a[])

Формат входных данных: Функцийя принмате на вход целые числа
Формат результата: Отсортированный исходный массив*/

enum
{
    SIZE = 20 // Размер массива
};

// Ввод массива с клавиатуры
void input_array(int arr[], int size);
// Печать массива
void printr_array(int arr[], int size);
// Сортировка: четные - нечетные
void sort_even_odd(int n, int a[]);

int main(void)
{
    int arr[SIZE] = {0};
    input_array(arr, SIZE);
    sort_even_odd(SIZE, arr);
    printr_array(arr, SIZE);
    return 0;
}

// ---------------------------------------------

void sort_even_odd(int n, int a[]) {
    int temp[n];
    int even_index = 0;
    int odd_index = n - 1;
    
    // Сначала размещаем четные элементы в начале временного массива
    for (int i = 0; i < n; i++) {
        if (a[i] % 2 == 0) {
            temp[even_index++] = a[i];
        }
    }
    
    // Затем размещаем нечетные элементы в конце временного массива в обратном порядке
    for (int i = n - 1; i >= 0; i--) {
        if (a[i] % 2 != 0) {
            temp[odd_index--] = a[i];
        }
    }
    
    // Копируем результат обратно в исходный массив
    for (int i = 0; i < n; i++) {
        a[i] = temp[i];
    }
}

void printr_array(int arr[], int size)
{
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

void input_array(int arr[], int size)
{
    for (int i = 0; i < size; i++) {
        scanf("%d", &arr[i]);
    }
}

