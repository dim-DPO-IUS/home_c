#include "temp_api.h"
#include <limits.h>
#include <stdio.h>

// Статистика по месяцу
void print_month_stats(const sensor *data, size_t count, uint8_t month)
{
    int sum = 0, min = INT_MAX, max = INT_MIN;
    size_t entries = 0;

    for (size_t i = 0; i < count; i++)
    {
        if (data[i].month == month)
        {
            sum += data[i].temperature;
            if (data[i].temperature < min) min = data[i].temperature;
            if (data[i].temperature > max) max = data[i].temperature;
            entries++;
        }
    }

    if (entries > 0)
    {
        printf("Month %02d:\n", month);
        printf("  Avg: %.2f°C\n", (float)sum / entries);
        printf("  Min: %d°C\n", min);
        printf("  Max: %d°C\n", max);
    }
    else
    {
        printf("No data for month %02d\n", month);
    }
}

// Статистика за год
void print_year_stats(const sensor *data, size_t count)
{
    int sum = 0, min = INT_MAX, max = INT_MIN;

    for (size_t i = 0; i < count; i++)
    {
        sum += data[i].temperature;
        if (data[i].temperature < min) min = data[i].temperature;
        if (data[i].temperature > max) max = data[i].temperature;
    }

    printf("Year Stats:\n");
    printf("  Avg: %.2f°C\n", (float)sum / count);
    printf("  Min: %d°C\n", min);
    printf("  Max: %d°C\n", max);
}