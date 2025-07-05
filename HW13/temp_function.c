#include "temp_function.h"

/*----------------------------------------------------------------------------*/
/*                            ВСПОМОГАТЕЛЬНЫЕ ФУНКЦИИ                         */
/*----------------------------------------------------------------------------*/

/**
 * @brief Проверяет, является ли год високосным
 *
 * @param year
 * @return int
 */
static inline int is_leap_year(uint16_t year)
{
    return (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0));
}

/**
 * @brief Проверяет, является ли символ цифрой.
 *
 * Функция проверяет, находится ли переданный символ в диапазоне от '0' до '9'.
 *
 * @param c Символ для проверки
 * @return int Возвращает 1 (true), если символ является цифрой, и 0 (false) в
 * противном случае
 */
static int is_digit(char c) { return c >= '0' && c <= '9'; }

/**
 * @brief Парсит целое число из строки, без обработки пробелов.
 * @brief ВНИМАНИЕ! Ожидает число без пробелов
 *
 * @param str
 * @param number
 * @return int
 */
static int parse_number(const char** str, int* number)
{
    int sign = 1;
    *number = 0;

    // Обработка знака
    if (**str == '-')
    {
        sign = -1;
        (*str)++;
    }
    else if (**str == '+')
    {
        (*str)++;
    }

    // Проверка, что символ - цифра
    if (!is_digit(**str)) return 0;

    // Парсинг числа с проверкой переполнения
    while (is_digit(**str))
    {
        int digit = **str - '0';

        // Проверка на переполнение для положительных чисел
        if (*number > INT_MAX / 10
            || (*number == INT_MAX / 10 && digit > INT_MAX % 10))
        {
            return 0; // Переполнение в положительную сторону
        }

        // Проверка на переполнение для отрицательных чисел
        if (*number < INT_MIN / 10
            || (*number == INT_MIN / 10 && -digit < INT_MIN % 10))
        {
            return 0; // Переполнение в отрицательную сторону
        }

        *number = *number * 10 + (sign * digit);
        (*str)++;
    }

    return 1;
}

/**
 * @brief Парсит одно поле из строки csv-файла с проверкой диапазона
 *
 * @param p
 * @param min_val
 * @param max_val
 * @param delimiter
 * @return int
 */
static int parse_csv_field(const char** p, int min_val, int max_val, char delimiter)
{
    int val;
    // Пропускаем пробелы перед числом
    while (**p == ' ') (*p)++;
    // Парсим число
    if (!parse_number(p, &val)) return -1;
    // Проверка диапазона
    if (val < min_val || val > max_val) return -1;
    // Пропускаем пробелы после числа
    while (**p == ' ') (*p)++;
    // Проверка разделителя (если требуется) Ожидался разделитель
    if (**p != delimiter && delimiter != '\0') return -1;
    // Пропускаем разделитель (если не конец строки)
    if (delimiter != '\0') (*p)++;

    return val;
}

/**
 * @brief Проверяет и парсит строку с данными датчика
 *
 * Функция выполняет валидацию и парсинг строки с показаниями датчика в формате:
 * "YYYY MM DD HH MM TT", где:
 * - YYYY - год (2000-2100)
 * - MM - месяц (1-12)
 * - DD - день (1-31, с проверкой по месяцам)
 * - HH - часы (0-23)
 * - MM - минуты (0-59)
 * - TT - температура (целое число)
 *
 * @param[in] line Входная строка для парсинга
 * @param[out] output Указатель на структуру sensor_t для записи результата
 * @return int 1 - успешный парсинг и валидация, 0 - ошибка формата или значений
 *
 * @details Алгоритм работы:
 * 1. Пропускает ведущие пробелы
 * 2. Последовательно парсит числа, разделенные пробелами
 * 3. Проверяет допустимость значений:
 *    - Год: 2000-2100
 *    - Месяц: 1-12
 *    - День: 1-31 с дополнительными проверками:
 *      - 30 дней для апреля, июня, сентября, ноября
 *      - 28 дней для февраля
 *    - Часы: 0-23
 *    - Минуты: 0-59
 *    - Температура: любое целое число
 * 4. Проверяет отсутствие лишних символов в конце
 *
 * @note Особенности:
 * - Поддерживает строки, оканчивающиеся на \n или \r
 * - Для февраля всегда 28 дней (без учета високосных лет)
 * - Допускает любое количество пробелов между числами
 * - Не проверяет переполнение при парсинге чисел
 *
 * @example Пример использования:
 * @code
 * sensor_t data;
 * if (is_valid_line("2023 12 31 23 59 25", &data)) {
 *     // Использование распарсенных данных
 *     printf("Температура: %d\n", data.temperature);
 * } else {
 *     printf("Ошибка формата строки\n");
 * }
 * @endcode
 *
 * @see sensor_t parse_number() is_whitespace()
 */
static int is_valid_line(const char* line, char delimiter, sensor* output)
{
    const char* p = line;

    // Парсим все поля по очереди
    int year = parse_csv_field(&p, 2000, 2100, delimiter);
    int month = parse_csv_field(&p, 1, 12, delimiter);
    int day = parse_csv_field(&p, 1, 31, delimiter);
    int hour = parse_csv_field(&p, 0, 23, delimiter);
    int minute = parse_csv_field(&p, 0, 59, delimiter);
    // Температура - последнее поле, без разделителя после
    int temperature = parse_csv_field(&p, -60, 60, '\0');

    // Проверка успешности парсинга всех полей
    if (year == -1 || month == -1 || day == -1 || hour == -1 || minute == -1
        || temperature == -1)
    {
        return 0;
    }

    // Записываем значения в структуру
    output->year = (uint16_t)year;
    output->month = (uint8_t)month;
    output->day = (uint8_t)day;
    output->hour = (uint8_t)hour;
    output->minute = (uint8_t)minute;
    output->temperature = (int8_t)temperature;

    // Проверка конца строки
    while (*p == ' ') p++;
    if (*p != '\0' && *p != '\n' && *p != '\r') return 0;

    // Проверка дней в месяце + високосный год
    if (output->month == 2)
    {
        int max_day = is_leap_year(output->year) ? 29 : 28;
        if (output->day > max_day) return 0;
    }
    else if ((output->month == 4 || output->month == 6 || output->month == 9
                 || output->month == 11)
        && output->day > 30)
    {
        return 0;
    }

    return 1;
}

/**
 * Инициализирует массив статистики по месяцам начальными значениями
 *

 */
static void init_temp_stats(temp_stats* stats, uint16_t year)
{
    stats->year = year;

    // Инициализация месячной статистики
    for (int i = 0; i < 12; i++)
    {
        stats->monthly[i].avg_temp = 0;
        stats->monthly[i].min_temp = INT8_MAX;
        stats->monthly[i].max_temp = INT8_MIN;
        stats->monthly[i].total_temp = 0;
        stats->monthly[i].count = 0;
    }

    // Инициализация годовой статистики
    stats->yearly.avg_temp = 0;
    stats->yearly.min_temp = INT8_MAX;
    stats->yearly.max_temp = INT8_MIN;
    stats->yearly.total_temp = 0;
    stats->yearly.count = 0;
}
/*----------------------------------------------------------------------------*/
/*                            СТЭК                                            */
/*----------------------------------------------------------------------------*/

/**
 * @brief Проверяет, является ли односвязный список пустым.
 *
 * Функция определяет, содержит ли список какие-либо элементы, проверяя,
 * является ли переданный указатель на голову списка нулевым (NULL).
 *
 * @param[in] top Указатель на головной узел списка (list_node*).
 * @return true — если список пуст (top == NULL), иначе false.
 *
 * @note Функция не изменяет состояние списка.
 * @see list_node, isEmpty()
 */
bool is_empty(node* top) { return top == NULL; }

/**
 * @brief Добавляет новый элемент в начало односвязного списка.
 *
 * Функция создает новый узел с переданными данными датчика и вставляет его
 * в начало списка. Если выделение памяти под новый узел не удается,
 * выводится сообщение об ошибке.
 *
 * @param[in,out] top Указатель на указатель головного узла списка.
 *                    После выполнения функции будет указывать на новый узел.
 * @param[in] data Данные датчика (структура sensor), которые необходимо
 * добавить.
 *
 * @note Функция динамически выделяет память под новый узел с помощью malloc().
 * @warning В случае ошибки выделения памяти функция выводит "Memory error!"
 *          и завершает работу без добавления элемента.
 * @see list_node, sensor, pop()
 */
void push(node** top, sensor data)
{
    // 1. Создаём новый узел.
    // Для стандартов до С99 и С++
    node* new_node = (node*)malloc(sizeof(node)); // Выделяем память
    // Для стандартов С99 и позже (C++ - нельзя) - автоматическое приведение
    // void* node* new_node = malloc(sizeof(node)); // Выделяем
    // память

    if (!new_node)
    {
        printf("Memory error!\n"); // Если память не выделилась
        return;
    }
    // 2. Записываем в него данные.
    new_node->data = data; // Записываем значение
    // 3. Делаем его next равным текущей вершине (top).
    new_node->next = *top; // Новый узел указывает на старую вершину (top)
    // 4. Перемещаем top на новый узел.
    *top = new_node; // Теперь вершина — новый узел
}

/**
 * @brief Удаляет и возвращает элемент из вершины стека (списка).
 *
 * Функция извлекает данные из головного узла списка, освобождает память узла
 * и перемещает указатель вершины на следующий элемент. Если список пуст,
 * выводит предупреждение и возвращает структуру sensor с нулевыми значениями.
 *
 * @param[in,out] top Указатель на указатель головного узла списка.
 *                    После выполнения будет указывать на следующий узел (или
 * NULL, если список стал пустым).
 * @return Данные датчика из удаленного узла. Если список пуст - возвращает
 * "пустую" структуру sensor с нулевыми значениями всех полей.
 *
 * @warning Если список пуст, выводит сообщение "Stack underflow!" и возвращает
 * нулевую структуру.
 * @note Функция освобождает память удаляемого узла с помощью free().
 * @see list_node, sensor, push(), isEmpty()
 */
sensor pop(node** top)
{
    sensor dummy = { 0 }; // Значение по умолчанию если стек пуст
    // 1. Проверяем, не пуст ли стек.
    if (is_empty(*top))
    {
        printf("Stack underflow!\n");
        // Возвращаем "пустую" структуру
        return dummy;
    }
    // 2. Запоминаем текущую вершину (temp = top).
    node* temp = *top;
    sensor popped = temp->data;
    // 3. Перемещаем top на следующий узел (top = top->next).
    // *top = (*top)->next;
    *top = temp->next;
    // 4. Возвращаем значение из temp и освобождаем память.
    free(temp);
    return popped;
}

/**
 * @brief Возвращает данные из вершины стека без удаления элемента.
 *
 * Функция позволяет получить данные из головного узла списка, не изменяя
 * сам список. Если список пуст, выводит предупреждение и возвращает
 * структуру sensor с нулевыми значениями.
 *
 * @param[in] top Указатель на головной узел списка.
 * @return Данные датчика из вершины стека. Если список пуст - возвращает
 *         структуру sensor с нулевыми значениями всех полей.
 *
 * @warning Если список пуст, выводит сообщение "Stack is empty!" и возвращает
 *          нулевую структуру.
 * @note Функция не изменяет состояние списка и не освобождает память.
 * @see list_node, sensor, pop(), isEmpty()
 */
sensor peek(node* top)
{
    sensor dummy = { 0 }; // Значение по умолчанию если стек пуст
    if (is_empty(top))
    {
        printf("Stack is empty!\n");
        // Возвращаем "пустую" структуру
        return dummy;
    }
    return top->data;
}

/**
 * @brief Очистка стека
 *
 * @param top
 */
void free_stack(node** top)
{
    while (!is_empty(*top))
    {
        pop(top);
    }
}

/**
 * @brief Выводит содержимое стека в стандартный вывод.
 *
 * Функция последовательно выводит все элементы стека, начиная с вершины,
 * в формате: "ГГГГ-ММ-ДД ЧЧ:ММ T°C". Для пустого стека выводит сообщение
 * "Stack is empty." В конце вывода всегда добавляет "NULL" для обозначения
 * конца списка.
 *
 * @param[in] top Указатель на вершину стека (головной узел списка).
 *
 * @note Формат вывода каждого элемента:
 *       "%04d-%02d-%02d %02d:%02d %3d°C\n" (дата, время, температура)
 * @warning Если передан NULL, выводит сообщение о пустом стеке.
 * @see list_node, sensor, isEmpty()
 */
void print_stack(const node* top, int num)
{
    if (top == NULL)
    {
        puts("Stack is empty.\n");
        return;
    }

    const node* current = top;
    num = num ? num : -1;
    int cnt = 0;
    while (current != NULL && cnt != num)
    {
        printf("%04d-%02d-%02d %02d:%02d %3d°C\n", current->data.year,
            current->data.month, current->data.day, current->data.hour,
            current->data.minute, current->data.temperature);
        current = current->next;
        cnt++;
    }

    if (current == NULL) printf("NULL\n");
}

/*----------------------------------------------------------------------------*/
/*                                ВВОД ДАННЫХ                                 */
/*----------------------------------------------------------------------------*/

/**
 * @brief Загружает данные датчиков из CSV-файла и помещает их в стек.
 *
 * Функция читает файл построчно, парсит данные в структуру `sensor` и добавляет
 * каждый корректный элемент в стек. Поддерживается формат CSV без заголовков:
 * `Год,Месяц,День,Часы,Минуты,Температура`.
 *
 * @param[in] filename Путь к CSV-файлу (например: "data.csv")
 * @param[in,out] top Указатель на указатель вершины стека. После выполнения
 *                    будет содержать новые элементы.
 * @return true - если файл прочитан успешно (даже если некоторые строки
 * пропущены), false - если не удалось открыть файл.
 *
 * @warning Требования к формату CSV:
 *  - Строго 6 числовых полей в строке
 *  - Разделитель - запятая
 *  - Без заголовков и кавычек
 * @note Некорректные строки пропускаются с выводом предупреждения.
 * @note Максимальная длина строки - 255 символов (остаток обрезается).
 *
 * @par Пример использования:
 * @code
 * #include "sensor_stack.h"
 *
 * int main() {
 *     list_node* stack = NULL;  // Инициализация пустого стека
 *
 *     if (!load_sensors_from_csv("sensors.csv", &stack)) {
 *         fprintf(stderr, "Ошибка загрузки файла!\n");
 *         return 1;
 *     }
 *
 *     printStack(stack);  // Вывод всех загруженных данных
 *
 *     // Очистка стека (если нужно)
 *     while (!isEmpty(stack)) {
 *         pop(&stack);
 *     }
 *
 *     return 0;
 * }
 * @endcode
 *
 * @par Пример содержимого CSV-файла:
 * @code
 * 2023,12,25,14,30,-5
 * 2023,12,26,09,15,2
 * 2023,12,27,18,45,-10
 * @endcode
 *
 * @see sensor, list_node, push(), pop(), printStack()
 */

size_t load_from_csv(
    const char* filename, node** top, char delimiter, load_stats* load_info)
{
    // Инициализация статистики
    memset(load_info, 0, sizeof(load_stats));
    // Запишем имя файла
    strncpy(load_info->filename, filename, sizeof(load_info->filename) - 1);

    FILE* file = fopen(filename, "r");
    if (!file)
    {
        perror("Failed to open file");
        return 0;
    }

    char line[256];
    sensor data;

    while (fgets(line, sizeof(line), file))
    {
        load_info->total_lines++;

        // Удаление символов новой строки
        line[strcspn(line, "\r\n")] = '\0';

        // Пустые строки и комментарии
        if (line[0] == '\0' || line[0] == '#')
        {
            fprintf(
                stderr, "Line %zu: Empty line - %s\n", load_info->total_lines, line);
            load_info->empty_lines++;
            continue;
        }

        // Валидация записи
        if (!is_valid_line(line, delimiter, &data))
        {
            fprintf(stderr, "Line %zu: Invalid data values - %s\n",
                load_info->total_lines, line);
            load_info->invalid_values++;
            continue;
        }

        // Все проверки пройдены - записываем
        push(top, data);
        load_info->valid_records++;
    }

    fclose(file);

    return load_info->valid_records;
}

/**
 * @brief
 *
 * @param load_info
 */
void print_load_stats(const load_stats* load_info)
{
    printf("\nFile loading statistics:\n");
    printf("--------------------------------\n");
    printf("File Name:             %s\n", load_info->filename);
    printf("Total lines processed: %zu\n", load_info->total_lines);
    printf("Empty lines/comments:  %zu\n", load_info->empty_lines);
    printf("Valid records:         %zu\n", load_info->valid_records);
    printf("Invalid format:        %zu\n", load_info->invalid_format);
    printf("Invalid values:        %zu\n", load_info->invalid_values);
    printf("--------------------------------\n");
}

/*----------------------------------------------------------------------------*/
/*                            СТАТИСТИКА                                      */
/*----------------------------------------------------------------------------*/

/**
 * @brief
 *
 * @param top
 */
temp_stats calculate_stats(node* top)
{
    temp_stats stats = { 0 };

    if (top == NULL)
    {
        printf("Stack is empty!\n");
        return stats;
    }
    // Инициализация статистики
    init_temp_stats(&stats, top->data.year);

    node* current = top;
    // Обработка данных
    while (current != NULL)
    {
        int month_idx = current->data.month - 1;
        int8_t temp = current->data.temperature;

        // Обновление месячной статистики
        stats.monthly[month_idx].total_temp += temp;
        if (temp < stats.monthly[month_idx].min_temp)
            stats.monthly[month_idx].min_temp = temp;
        if (temp > stats.monthly[month_idx].max_temp)
            stats.monthly[month_idx].max_temp = temp;
        stats.monthly[month_idx].count++;

        // Обновление годовой статистики
        stats.yearly.total_temp += temp;
        if (temp < stats.yearly.min_temp) stats.yearly.min_temp = temp;
        if (temp > stats.yearly.max_temp) stats.yearly.max_temp = temp;
        stats.yearly.count++;

        current = current->next;
    }

    // Расчет средних значений по месяцам
    for (int i = 0; i < 12; i++)
    {
        if (stats.monthly[i].count > 0)
        {
            stats.monthly[i].avg_temp
                = (float)stats.monthly[i].total_temp / stats.monthly[i].count;
        }
    }

    // Правильный расчет средней за год!
    if (stats.yearly.count > 0)
    {
        stats.yearly.avg_temp = (float)stats.yearly.total_temp / stats.yearly.count;
    }

    // Вывод результатов
    // print_monthly_stats(&stats, 0);
    // print_yearly_stats(&stats);

    return stats;
}

/**
 * @brief Вывод месячной статистики
 *
 * @param stats
 */
void print_monthly_stats(const temp_stats* stats, uint8_t month)
{
    // Проверка корректности параметра month
    if (month > 12)
    {
        printf("Error: Invalid month number! Must be 0 (all months) or 1-12.\n");
        return;
    }

    // Заголовок таблицы
    printf("------------------------------------------------------\n");
    printf(" Year | Month | Count | Avg Temp | Max Temp | Min Temp\n");
    printf("------|-------|-------|----------|----------|---------\n");

    if (month == 0)
    {
        // Вывод статистики по всем месяцам
        for (int i = 0; i < 12; i++)
        {
            if (stats->monthly[i].count > 0)
            {
                printf("%5d | %5d | %5d | %8.1f | %8d | %8d\n", stats->year, i + 1,
                    stats->monthly[i].count, stats->monthly[i].avg_temp,
                    stats->monthly[i].max_temp, stats->monthly[i].min_temp);
            }
        }
    }
    else
    {
        // Вывод статистики за конкретный месяц
        int month_idx = month - 1;
        if (stats->monthly[month_idx].count > 0)
        {
            printf("%5d | %5d | %5d | %8.1f | %8d | %8d\n", stats->year, month,
                stats->monthly[month_idx].count, stats->monthly[month_idx].avg_temp,
                stats->monthly[month_idx].max_temp,
                stats->monthly[month_idx].min_temp);
        }
        else
        {
            printf("No data available for month %d\n", month);
        }
    }
}

/**
 * @brief Вывод годовой статистики
 *
 * @param stats
 */
void print_yearly_stats(const temp_stats* stats)
{
    printf("\nYearly statistics:\n");
    printf("-----------------------------------------------\n");
    printf(" Year | Count | Avg Temp | Max Temp | Min Temp\n");
    printf("------|-------|----------|----------|----------\n");
    printf("%5d | %5d | %8.1f | %8d | %8d\n",
        stats->year, // Год
        stats->yearly.count, // Общее количество измерений
        stats->yearly.avg_temp, // Средняя за год
        stats->yearly.max_temp, // Абсолютный максимум
        stats->yearly.min_temp); // Абсолютный минимум
    printf("\n");
}

/*----------------------------------------------------------------------------*/
/*                                  СОРТИРОВКА                                */
/*----------------------------------------------------------------------------*/

/**
 * @brief Функция сравнения для qsort (по дате и времени)
 *
 * @param a
 * @param b
 * @return int
 */
int compare_by_date(const void* a, const void* b)
{
    const sensor* s1 = (const sensor*)a;
    const sensor* s2 = (const sensor*)b;

    if (s1->year != s2->year) return s1->year - s2->year;
    if (s1->month != s2->month) return s1->month - s2->month;
    if (s1->day != s2->day) return s1->day - s2->day;
    if (s1->hour != s2->hour) return s1->hour - s2->hour;
    return s1->minute - s2->minute;
}

/**
 * @brief
 *
 * @param a
 * @param b
 * @return int
 */
int compare_by_temp(const void* a, const void* b)
{
    sensor* s1 = (sensor*)a;
    sensor* s2 = (sensor*)b;

    return s1->temperature - s2->temperature;
}

/**
 * @brief
 *
 * @param top
 * @param td 0: сортируем по температуре, 1: сортируем по дате
 */
void sort_stack(node** top, load_stats load_info, char td)
{
    int size = (int)load_info.valid_records;

    // 1. Извлекаем все элементы в массив
    sensor temp_arr[size];
    int count = 0;

    while (!is_empty(*top))
    {
        temp_arr[count++] = pop(top);
    }

    // 2. Сортируем массив
    if (td == 'd')
        qsort(temp_arr, count, sizeof(sensor), compare_by_date);
    else if (td == 't')
        qsort(temp_arr, count, sizeof(sensor), compare_by_temp);

    // 3. Заполняем стек обратно (в обратном порядке, чтобы верхний элемент
    // был минимальным)
    for (int i = count - 1; i >= 0; i--)
    {
        push(top, temp_arr[i]);
    }
}

/*----------------------------------------------------------------------------*/
/*                                  КОМАНДНАЯ СТРОКА                          */
/*----------------------------------------------------------------------------*/

/**
 * @brief Парсинг аргументов командной строки
 * @param argc Количество аргументов
 * @param argv Массив аргументов
 * @param args Структура для результатов
 * @return 0 - успешно, 1 - вывод справки, -1 - ошибка
 */
int parse_arguments(int argc, char* argv[], cmd_args* args)
{
    // Вызов без аргументов
    if (argc == 1)
    {
        printf(HELP_MSG, argv[0]);
        return 1;
    }

    // Обнуляем структуру
    memset(args, 0, sizeof(cmd_args));
    // Начинаем с 1, так как argv[0] - имя программы
    for (int i = 1; i < argc; i++)
    {
        char* arg = argv[i];

        // Пропускаем не-флаги (например, значения аргументов)
        if (arg[0] != '-') continue;

        // Проверяем, что после флага есть значение (если требуется)
        if (i + 1 >= argc || argv[i + 1][0] == '-')
        {
            switch (arg[1])
            {
            case 'f':
                fprintf(stderr, "Error: Missing filename after -f\n");
                return -1;
            case 'm': fprintf(stderr, "Error: Missing month after -m\n"); return -1;
            case 'y': fprintf(stderr, "Error: Missing year after -y\n"); return -1;
            case 'p': fprintf(stderr, "Error: Missing count after -p\n"); return -1;
            case 's': fprintf(stderr, "Error: Missing count after -s\n"); return -1;
            }
        }

        switch (arg[1])
        {
        case 'f': args->filename = argv[i + 1]; break;
        case 'm': sscanf(argv[i + 1], "%hhu", &args->month); break;
        case 'y': sscanf(argv[i + 1], "%hu", &args->year); break;
        case 'p': sscanf(argv[i + 1], "%hhu", &args->printdb); break;
        case 's': sscanf(argv[i + 1], "%c", &args->sort); break;
        case 'h': printf(HELP_MSG, argv[0]); return 1;
        default:
            fprintf(stderr, "Ошибка: неизвестная опция '-%c'\n", arg[1]);
            return -1;
        }
    }

    // Проверка обязательных параметров
    if (args->filename == NULL)
    {
        fprintf(stderr, "Ошибка: не указан входной файл (используйте -f)\n");
        return -1;
    }

    return 0;
}

/*----------------------------------------------------------------------------*/
/*                                                                            */
/*----------------------------------------------------------------------------*/