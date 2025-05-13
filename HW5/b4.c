#include <inttypes.h>
#include <stdio.h>

// Ввести целое число и определить, верно ли, что в нём ровно 3 цифры.

int main(void)
{
    int16_t a = 0;
    int8_t result = 1;

    scanf("%hd", &a);

    while (a)
        result += (a /= 10) != 0;

    printf("%s\n", result == 3 ? "YES" : "NO");

    return 0;
}