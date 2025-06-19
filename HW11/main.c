#include "temp_api.h"
#include <stdio.h>

#define MAX_ENTRIES 100

int main()
{
    sensor data[MAX_ENTRIES] = {{2023, 1, 15, 12, 30, -5},
                                {2023, 1, 15, 18, 45, -7},
                                {2023, 2, 20, 9, 15, 10},
                                {2023, 2, 21, 15, 20, 12},
                                {2023, 3, 10, 14, 0, 15}};
    size_t count = 5;

    // Пример вызова функций
    print_month_stats(data, count, 1); // Статистика за январь
    print_month_stats(data, count, 2); // Статистика за февраль
    print_year_stats(data, count);     // Статистика за год

    return 0;
}