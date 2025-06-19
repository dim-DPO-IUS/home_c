#ifndef TEMP_API_H
#define TEMP_API_H

#include <stdint.h> // uint*_t
#include <stdio.h>  // size_t

// Структура для хранения данных о температуре
typedef struct
{
    uint16_t year;
    uint8_t month;
    uint8_t day;
    uint8_t hour;
    uint8_t minute;
    int8_t temperature;
} sensor;

// Прототипы функций
void print_month_stats(const sensor *data, size_t count, uint8_t month);
void print_year_stats(const sensor *data, size_t count);

#endif // TEMP_API_H