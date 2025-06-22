#ifndef TEMP_API_H
#define TEMP_API_H
/*******************************************************************
 *                               FILE HEADER                       *
 *                                                                 *
 * Project:    Course Project                                      *
 * File:       temp_api.h                                          *
 * Author:     Konoplev Dmitriy                                    *
 * Created:    2025-06-19                                          *
 *******************************************************************/
#include <stdio.h>
#include <stdint.h> // uint*_t
#include <limits.h> // MIN/MAX
//
#include <stdlib.h>
#include <time.h> // ГСЧ

// Структура для хранения данных о температуре
struct sensor
{
    uint16_t year;
    uint8_t month;
    uint8_t day;
    uint8_t hour;
    uint8_t minute;
    int8_t temperature;
};

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
void print_stats(struct sensor* data,
                 size_t count,
                 uint8_t month,
                 uint16_t year);

// Добавление одной записи. Создание массива структур
void add_record(struct sensor* data,
                int number,
                uint16_t year,
                uint8_t month,
                uint8_t day,
                uint8_t hour,
                uint8_t minute,
                int8_t t);

// Добавление набора записей
int add_records(struct sensor* data);

// Поиск индекса записи
int find_index(struct sensor data[],
               int size,
               uint16_t year,
               uint8_t month,
               uint8_t day,
               uint8_t hour,
               uint8_t minute);

// Удаление по индексу (возвращает новый размер)
int remove_by_index(struct sensor* data, int size, int index);

// Удаление по дате (возвращает новый размер)
int remove_by_date(struct sensor* data,
                   int size,
                   uint16_t year,
                   uint8_t month,
                   uint8_t day);

// Печать массива записей
void print(struct sensor* data, int number);

//
void cgangeIJ(struct sensor* data, int i, int j);

// Упорядочить по дате
void sort_by_date(struct sensor* data, int n);

// Упорядочить по температуре по неубыванию
void sort_by_t(struct sensor* data, int n);

//
unsigned int date_to_int(struct sensor* data);

// Функция для генерации случайного числа в диапазоне
int random_int(int min, int max);

// Генератор записей (возвращает количество сгенерированных записей)
int generate_sensor_data(struct sensor* data, int count);

// Парсер аргументов командной строки
// Возвращает:
//  1: при вызове справки
//  -1: при ошибке
int parse_arguments(int argc, char* argv[], struct cmd_args* args);

#endif // TEMP_API_H