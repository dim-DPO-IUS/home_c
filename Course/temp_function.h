#ifndef TEMP_FUNCTION_H
#define TEMP_FUNCTION_H
//
#include <limits.h> // Для INT_MAX и INT_MIN
#include <stdbool.h> // true, false
#include <stdint.h> // inttypes
#include <stdio.h>
#include <stdlib.h> // free, malloc ...
#include <string.h> // memset

/**
 * @brief Почему двунаправленный список (Doubly Linked List), а не стек
реализованный как односвязный список.

Стек приводит к двум неудобствам:
1. Данные выводятся в обратном порядке относительно файла (последняя запись файла
печатается первой).
2. Сортировка требует извлечения всех данных во временный массив, что неэффективно по
памяти.
Как работает Двунаправленный список (Doubly Linked List): Каждый элемент имеет
ссылки и на следующий (next), и на предыдущий (prev) элемент.
Плюсы:
    Можно обходить как от начала к концу (как в файле), так и от конца к началу
(как в сиеке на односвязном списке).
    Гибкость: поддерживает и стековые, и очередевые операции.
    Сортировка реализуется эффективнее (например, вставками).
Минусы:
    Чуть сложнее реализация (нужно обновлять два указателя вместо одного).
Когда использовать: Если нужны оба варианта обхода (прямой и обратный) или
сортировка.
 *
 */

/*----------------------------------------------------------------------------*/
/*                              CONSTANTS                                     */
/*----------------------------------------------------------------------------*/

/// Имя лог-файла для записи логов загрузки из файла данных
#define LOG_FILENAME "load_errors.log"

/// Start message for command line interface
static const char START_MSG[]
    = "--------------------------------------\n"
      "Temperature Data Analysis Tool\n"
      "--------------------------------------\n"
      "Features:\n"
      "- CSV data import\n"
      "- Temperature statistics analysis\n"
      "- Custom period filtering\n"
      "- Data sorting options\n"
      "- Automatic error logging to 'load_errors.log'\n\n"
      "Usage: program -f <filename.csv> [options]\n\n"
      "Required option:\n"
      "-f <file>    Specify input CSV file (required)\n\n"
      "Analysis options:\n"
      "-m <month>   Show stats for specific month (1-12)\n\n"
      "Data output options:\n"
      "-p <N>       Print first N records from dataset\n"
      "-s <criteria> Sort data (d - by date, t - by temperature)\n\n"
      "Other options:\n"
      "-h           Show this help message\n\n"
      "Error Handling:\n"
      "- Errors are logged to 'load_errors.log'\n"
      "- Invalid values are automatically skipped\n"
      "- Empty lines and comments are ignored\n"
      "\n";

/// Help message for command line interface
static const char HELP_MSG[]
    = "--------------------------------------\n"
      "Temperature Data Analysis Tool. \n"
      "--------------------------------------\n"
      "Available options:\n"
      " -h            Show this help message\n"
      " -f <file>     Specify input CSV file\n"
      " -m <month>    Show statistics for specific month (1-12)\n"
      " -p <N>        Print first N records from the dataset\n"
      " -s <criteria> Sort data (d - by date, t - by temperature)\n"
      "\n";

/*----------------------------------------------------------------------------*/
/*                            ОПРЕДЕЛЕНИЯ ТИПОВ                               */
/*----------------------------------------------------------------------------*/

/**
 * @brief Битовые флаги для режимов параметров командной строки
 *
 */
typedef enum run_mode {
    MODE_NONE = 0, // 0b0000
    MODE_FILE = 1 << 0, // 0b0001 (обязательный)
    MODE_MONTH = 1 << 1, // 0b0010
    MODE_PRINT = 1 << 2, // 0b0100
    MODE_SORT = 1 << 3, // 0b1000

    // Комбинации режимов
    MODE_FILE_MONTH = MODE_FILE | MODE_MONTH, // 0b0011
    MODE_FILE_PRINT = MODE_FILE | MODE_PRINT, // 0b0101
    MODE_FILE_SORT = MODE_FILE | MODE_SORT, // 0b1001
    MODE_FILE_SORT_PRINT = MODE_FILE | MODE_PRINT | MODE_SORT, // 0b1101
    /*-----------------------------------------------------------*/
    // MODE_FILE_MONTH_PRINT = MODE_FILE | MODE_MONTH | MODE_PRINT, // 0b0111
    // MODE_FILE_MONTH_SORT = MODE_FILE | MODE_MONTH | MODE_SORT, // 0b1011
    // MODE_FULL = MODE_FILE | MODE_MONTH | MODE_PRINT | MODE_SORT // 0b1111
} run_mode;

/**
 * @brief Параметры командной строки
 *
 * Содержит разобранные аргументы командной строки для работы программы:
 */
typedef struct cmd_args {
    const char* filename; ///< Имя входного CSV-файла с данными
    uint8_t month; ///< Месяц для анализа (1-12, 0 - все месяцы)
    uint8_t printdb; ///< Количество записей для печати
    char sort; ///< Критерий сортировки ('d'-дата, 't'-температура)
    run_mode mode; ///< Флаги установленных параметров
} cmd_args;

/**
 * @brief Структура, представляющая данные датчика температуры.
 *
 * Используется для хранения метки времени и температуры.
 * Поддерживает только годы с 2000 по 2100, температуру в диапазоне -128..+127
 * °C.
 *
 * @note Для февраля високосные годы не проверяются автоматически.
 */
#pragma pack(push, 1) // Отключить выравнивание
typedef struct sensor {
    uint16_t year; ///< Год (2000-2100)
    uint8_t month : 4; ///< Месяц (1-12)
    uint8_t day : 5; ///< День (1-31)
    uint8_t hour : 5; ///< Часы (0-23)
    uint8_t minute : 6; ///< Минуты (0-59)
    int8_t temperature; ///< Температура (°C)
} sensor;
#pragma pack(pop) // Вернуть выравнивание

/**
 * @brief Узел связного списка, содержащий данные датчика.
 *
 * Структура представляет собой узел односвязного списка, который хранит:
 * - Данные датчика (тип sensor)
 * - Указатель на следующий узел в списке
 *
 * @typedef list_node
 *
 * @var list_node::data
 * Данные датчика, хранящиеся в узле
 * @var list_node::next
 * Указатель на следующий узел списка. Если это последний узел, равен NULL.
 */
typedef struct node {
    sensor data; // данные
    struct node* next; // следующий элемент
    struct node* prev; // предыдущий элемент
} node;

/**
 * @brief Статистика температурных данных
 *
 * Содержит агрегированные данные по температуре:
 * - Ежемесячная статистика (массив из 12 элементов)
 * - Годовая статистика (суммарные значения)
 */
typedef struct temp_stats {
    uint16_t year; ///< Год наблюдений
    struct {
        float avg_temp; ///< Средняя температура
        int8_t min_temp; ///< Минимальная температура
        int8_t max_temp; ///< Максимальная температура
        int32_t total_temp; ///< Сумма температур для точного расчета
        int count; ///< Количество измерений
    } monthly[12], ///< Месячная статистика (0-январь..11-декабрь)
        yearly; ///< Годовая статистика
} temp_stats;

/**
 * @brief Статистика загрузки данных из файла
 *
 * Содержит информацию о результате загрузки и парсинга данных:
 */
typedef struct load_stats {
    char filename[256]; ///< Имя файла-источника данных
    char logfile[256]; ///< Имя файла для записи ошибок
    bool log_success; // Успешно ли открыт лог-файл
    size_t first_error_line; // Первая строка с ошибкой
    size_t total_lines; ///< Всего строк в файле
    size_t empty_lines; ///< Пустых строк или комментариев
    size_t valid_records; ///< Успешно загруженных записей
    size_t invalid_format; ///< Строк с неверным форматом
    size_t invalid_values; ///< Строк с некорректными значениями
} load_stats;

/*----------------------------------------------------------------------------*/
/*                            Doubly Linked List (LIFO)                       */
/*----------------------------------------------------------------------------*/

/**
 * @brief Проверяет, является ли список пустым.
 *
 * @param head Указатель на голову списка.
 * @return true — если список пуст (head == NULL), иначе false.
 */
bool is_empty(node* top);

/**
 * @brief Добавляет новый элемент в начало списка.
 *
 * @param head Указатель на указатель головы списка.
 * @param tail Указатель на указатель хвоста списка.
 * @param data Данные для добавления.
 */
void push(node** head, node** tail, sensor data);

/**
 * @brief Удаляет и возвращает элемент из начала списка.
 *
 * @param head Указатель на указатель головы списка.
 * @param tail Указатель на указатель хвоста списка.
 * @return sensor Данные удаленного узла или нулевая структура, если список пуст.
 */
sensor pop(node** head, node** tail);

/**
 * @brief Возвращает данные из начала списка без удаления.
 *
 * @param head Указатель на голову списка.
 * @return sensor Данные первого узла или нулевая структура, если список пуст.
 */
sensor peek(node* top);

/**
 * @brief Освобождает память, занятую списком.
 *
 * @param head Указатель на указатель головы списка.
 * @param tail Указатель на указатель хвоста списка.
 */
void free_list(node** head, node** tail);

/**
 * @brief Выводит содержимое списка.
 *
 * @param current Указатель на текущий узел (для рекурсивного обхода).
 * @param num Количество элементов для вывода (0 — все).
 * @param reverse Флаг обратного порядка вывода.
 */
void print_list(const node* head, int num, bool reverse);

/*----------------------------------------------------------------------------*/
/*                                ВВОД ДАННЫХ                                 */
/*----------------------------------------------------------------------------*/

/**
 * @brief Читает данные датчиков из CSV-файла и помещает их в стек
 * @param filename Имя CSV-файла для чтения
 * @param top Указатель на указатель вершины стека
 * @return true если файл успешно прочитан, false при ошибке
 */
size_t load_from_csv(const char* filename, node** head, node** tail, char delimiter,
    load_stats* load_info);

/**
 * @brief Выводит статистику загрузки данных
 * @param load_info Указатель на структуру со статистикой
 * @return void
 */
void print_load_stats(const load_stats* load_info);

/*----------------------------------------------------------------------------*/
/*                            СТАТИСТИКА                                      */
/*----------------------------------------------------------------------------*/

/**
 * @brief Вычисляет статистику по данным в стеке
 * @param top Указатель на вершину стека с данными
 * @return Структура temp_stats с рассчитанной статистикой
 */
temp_stats calculate_stats(node* head);

/**
 * @brief Выводит месячную статистику температур
 * @param stats Указатель на структуру с данными статистики
 * @param month Номер месяца (1-12) или 0 для вывода всех месяцев
 * @return void
 */
void print_monthly_stats(const temp_stats* stats, uint8_t month);

/**
 * @brief Выводит годовую статистику температур
 * @param stats Указатель на структуру с данными статистики
 * @return void
 */
void print_yearly_stats(const temp_stats* stats);

/*----------------------------------------------------------------------------*/
/*                                  СОРТИРОВКА                                */
/*----------------------------------------------------------------------------*/

/**
 * @brief Сортирует двунаправленный список по указанному критерию.
 *
 * @param head Указатель на указатель головы списка.
 * @param tail Указатель на указатель хвоста списка.
 * @param criteria Критерий сортировки:
 *                'd' - по дате (год → месяц → день → час → минута)
 *                't' - по температуре
 *
 * @note Использует временный массив для сортировки через qsort().
 * @note Сохраняет исходный порядок при равных значениях (стабильная сортировка).
 */
void sort_list(node** head, node** tail, char criteria);

/*----------------------------------------------------------------------------*/
/*                                  КОМАНДНАЯ СТРОКА                          */
/*----------------------------------------------------------------------------*/

/**
 * @brief Парсинг аргументов командной строки
 * @param argc Количество аргументов
 * @param argv Массив аргументов
 * @param args Структура для результатов
 * @return 0 - успешно, 1 - вывод справки, -1 - ошибка, 2 - вызов без аргументов
 */
int parse_arguments(int argc, char* argv[], cmd_args* args);

#endif // TEMP_FUNCTION_H