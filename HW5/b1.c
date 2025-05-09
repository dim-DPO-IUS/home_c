#include<stdio.h>
#include<inttypes.h>

// Ввести натуральное число вывести квадраты и кубы всех чисел от 1 до этого числа. Число не превосходит 100.

int main(void)
{
    uint8_t a=0;

    scanf("%hhu", &a);
    
    for(int i=1; i<=a; i++)
        printf("%d %d %d\n", i, i*i, i*i*i);

    return 0;
}