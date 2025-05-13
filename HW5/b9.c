#include <inttypes.h>
#include <stdio.h>

// Ввести целое число и определить, верно ли, что все его цифры четные.

int main()
{
    int n = 0, res = 0;
    scanf("%d", &n);

    while (n) {
        if (res = n % 2 != 0)
            break;
        n /= 10;
    }
    printf("%s\n", res ? "NO" : "YES");
}