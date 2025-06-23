#ifndef TEMP_API_H
#define TEMP_API_H

/*******************************************************************************
 *                               FILE HEADER                                   *
 *                                                                             *
 * Project:    Course Project                                                  *
 * File:       temp_api.h                                                      *
 * Author:     Konoplev Dmitriy                                                *
 * Created:    2025-06-19                                                      *
 * Description: API for temperature data processing                            *
 *******************************************************************************/

/*----------------------------------------------------------------------------*/
/*                                INCLUDES                                    */
/*----------------------------------------------------------------------------*/
#include <stdio.h>
#include <stdint.h> // uint*_t types
#include <limits.h> // MIN/MAX constants
#include <stdlib.h>
#include <time.h> // Random number generation

/*----------------------------------------------------------------------------*/
/*                              DATA STRUCTURES                               */
/*----------------------------------------------------------------------------*/

/**
 * @brief Temperature sensor data structure
 */
typedef struct
{
    uint16_t year;      ///< Year (e.g. 2025)
    uint8_t month;      ///< Month (1-12)
    uint8_t day;        ///< Day (1-31)
    uint8_t hour;       ///< Hour (0-23)
    uint8_t minute;     ///< Minute (0-59)
    int8_t temperature; ///< Temperature in Celsius
} sensor;

// struct sensor
// {
//     uint16_t year;
//     uint8_t month;
//     uint8_t day;
//     uint8_t hour;
//     uint8_t minute;
//     int8_t temperature;
// };

// Структура для хранения ключей из командной строки
struct cmd_args
{
    uint16_t year;        // -y
    uint8_t month;        // -m
    const char* filename; // -f
    uint8_t printdb;      // -p
    // int debug_mode;
    // int seed;
};

// Глобальная строка со справкой (используется в парсере ком. строки)
static const char* HELP_MSG =
    "Использование: %s [опции]\n"
    "Опции:\n"
    " -f <файл>     Указать входной CSV файл (обязательный)\n"
    " -h            Показать эту справку\n"
    " -m <месяц>    Фильтровать по месяцу (1-12)\n"
    " -y <год>      Фильтровать по году\n"
    " -p <печать>   Печать первых N записей\n";

//-------------------------------------------------------

// Вывод статистики ИЛИ за месяц ИЛИ за год
// Или month или year должны быть равны 0
void print_stats(sensor* data,
                 size_t count,
                 uint8_t month,
                 uint16_t year);

// Добавление одной записи. Создание массива структур
void add_record(sensor* data,
                int number,
                uint16_t year,
                uint8_t month,
                uint8_t day,
                uint8_t hour,
                uint8_t minute,
                int8_t t);

// Добавление набора записей
int add_records(sensor* data, int count);

// Поиск индекса записи
int find_index(sensor data[],
               int size,
               uint16_t year,
               uint8_t month,
               uint8_t day,
               uint8_t hour,
               uint8_t minute);

// Удаление по индексу (возвращает новый размер)
int remove_by_index(sensor* data, int size, int index);

// Удаление по дате (возвращает новый размер)
int remove_by_date(sensor* data,
                   int size,
                   uint16_t year,
                   uint8_t month,
                   uint8_t day);

// Печать массива записей
void print(sensor* data, int number);

//
void cgangeIJ(sensor* data, int i, int j);

// Упорядочить по дате
void sort_by_date(sensor* data, int n);

// Упорядочить по температуре по неубыванию
void sort_by_t(sensor* data, int n);

//
unsigned int date_to_int(sensor* data);

// Функция для генерации случайного числа в диапазоне
int random_int(int min, int max);

// Генератор записей (возвращает количество сгенерированных записей)
int generate_sensor_data(sensor* data, int count);

// Парсер аргументов командной строки
// Возвращает:
//  1: при вызове справки
//  -1: при ошибке
int parse_arguments(int argc, char* argv[], struct cmd_args* args);

#endif // TEMP_API_H