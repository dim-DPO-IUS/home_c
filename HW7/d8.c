#include <inttypes.h>
#include <stdio.h>

/*От A до B
Составить рекурсивную функцию, Выведите все числа от A до B включительно, в порядке возрастания, если A < B, или в порядке убывания в противном случае.
Формат входных данных: Два целых числа через пробел.
Формат результата: Последовательность целых чисел.
*/

void printAB(int32_t a, int32_t b);

int main(void)
{
    int32_t a = 0, b = 0;
    scanf("%d%d", &a, &b);
    printAB(a, b);
    return 0;
}

void printAB(int32_t a, int32_t b)
{
    if (a == b) {
        printf("%d", a);
        return;
    }

    printf("%d ", a);

    if (a < b)
        printAB(a + 1, b);
    else
        printAB(a - 1, b);
}