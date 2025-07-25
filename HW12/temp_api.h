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
#include <string.h>
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
} sensor_t;

/**
 * @brief Command line arguments structure
 */
typedef struct
{
    uint16_t year;        ///< Year filter (-y)
    uint8_t month;        ///< Month filter (-m)
    const char* filename; ///< Input CSV file (-f)
    uint8_t printdb;      ///< Print first N records (-p)
    // int debug_mode;       ///< Debug mode flag (reserved)
    // int seed;             ///< Random seed (reserved)
} cmd_args_t;

/*----------------------------------------------------------------------------*/
/*                              CONSTANTS                                     */
/*----------------------------------------------------------------------------*/

/// Help message for command line interface
static const char* HELP_MSG =
    "Использование: %s [опции]\n"
    "Опции:\n"
    " -f <file>     Указать входной CSV файл (обязательный)\n"
    " -h            Показать эту справку\n"
    " -m <month>    Фильтровать по месяцу (1-12)\n"
    " -y <year>     Фильтровать по году\n"
    " -p <print>    Печать первых N записей\n";

/*----------------------------------------------------------------------------*/
/*                            API DECLARATIONS                                */
/*----------------------------------------------------------------------------*/

/*---------------------------- Data Manipulation -----------------------------*/

/**
 * @brief Add a single temperature record to the dataset
 * @param data Pointer to sensor data array
 * @param number Current number of records
 * @param year Year value
 * @param month Month value (1-12)
 * @param day Day value (1-31)
 * @param hour Hour value (0-23)
 * @param minute Minute value (0-59)
 * @param t Temperature value
 */
void add_record(sensor_t* data,
                int number,
                uint16_t year,
                uint8_t month,
                uint8_t day,
                uint8_t hour,
                uint8_t minute,
                int8_t t);

/**
 * @brief Add multiple temperature records
 * @param data Pointer to sensor data array
 * @param count Number of records to add
 * @return Total number of records after addition
 */
int add_records(sensor_t* data, int count);

/**
 * @brief Find index of a specific record
 * @param data Sensor data array
 * @param size Current array size
 * @param year Year to search
 * @param month Month to search (1-12)
 * @param day Day to search (1-31)
 * @param hour Hour to search (0-23)
 * @param minute Minute to search (0-59)
 * @return Index of found record or -1 if not found
 */
int find_index(sensor_t data[],
               int size,
               uint16_t year,
               uint8_t month,
               uint8_t day,
               uint8_t hour,
               uint8_t minute);

/**
 * @brief Remove record by index
 * @param data Sensor data array
 * @param size Current array size
 * @param index Index to remove
 * @return New array size after removal
 */
int remove_by_index(sensor_t* data, int size, int index);

/**
 * @brief Remove records by date
 * @param data Sensor data array
 * @param size Current array size
 * @param year Year to remove
 * @param month Month to remove (1-12)
 * @param day Day to remove (1-31)
 * @return New array size after removal
 */
int remove_by_date(sensor_t* data,
                   int size,
                   uint16_t year,
                   uint8_t month,
                   uint8_t day);

/*---------------------------- Data Processing -------------------------------*/

/**
 * @brief Print temperature statistics for a month or year
 * @param data Sensor data array
 * @param count Number of records
 * @param month Month to filter (0 for all months)
 * @param year Year to filter (0 for all years)
 */
void print_stats(sensor_t* data, size_t count, uint8_t month, uint16_t year);

/**
 * @brief Print sensor data records
 * @param data Sensor data array
 * @param number Number of records to print
 */
void print(sensor_t* data, int number);

/**
 * @brief Sort records by date
 * @param data Sensor data array
 * @param n Number of records
 */
void sort_by_date(sensor_t* data, int n);

/**
 * @brief Sort records by temperature (ascending)
 * @param data Sensor data array
 * @param n Number of records
 */
void sort_by_t(sensor_t* data, int n);

/*---------------------------- Data Generation -------------------------------*/

/**
 * @brief Generate random sensor data
 * @param data Sensor data array
 * @param count Number of records to generate
 * @return Number of generated records
 */
int generate_sensor_data(sensor_t* data, int count);

/*---------------------------- Command Line Interface ------------------------*/

/**
 * @brief Parse command line arguments
 * @param argc Argument count
 * @param argv Argument vector
 * @param args Output structure for parsed arguments
 * @return 1 if help was requested, -1 on error, 0 on success
 */
int parse_arguments(int argc, char* argv[], cmd_args_t* args);

#endif // TEMP_API_H