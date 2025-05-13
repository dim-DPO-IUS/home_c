#include <inttypes.h>
#include <math.h>
#include <stdio.h>

// Проверить число на простоту.
// Формат входных данных: Натуральное число
// Формат результата: Если число является простым напечатать YES, иначе NO

int main(void)
{
    uint32_t num = 1, lim = 0;
    scanf("%u", &num);

    uint8_t res = 1; // 1-YES, 0-NO

    if (num < 2 || num % 2 == 0 && num != 2)
        res = 0;
    else {
        lim = sqrt(num);
        for (uint32_t i = 3; i <= lim; i += 2) {
            if (num % i == 0) {
                res = 0;
                break;
            }
        }
    }

    printf("%s\n", res ? "YES" : "NO");
    return 0;
}