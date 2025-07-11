#include "temp_function.h"

/*----------------------------------------------------------------------------*/
/*                            ВСПОМОГАТЕЛЬНЫЕ ФУНКЦИИ                         */
/*----------------------------------------------------------------------------*/

/**
 * @brief Проверяет, является ли год високосным
 *
 * Функция определяет, является ли указанный год високосным согласно григорианскому
 * календарю.
 *
 * @param[in] year Год для проверки (должен быть в григорианском календаре)
 * @return 1 если год високосный, 0 в противном случае
 *
 * @note Алгоритм соответствует правилам григорианского календаря:
 *       - Год високосный, если он делится на 4
 *       - Но не високосный, если делится на 100
 *       - Однако високосный, если делится на 400
 * @note Корректно работает для всех годов григорианского календаря (с 1582 года)
 * @warning Для годов до введения григорианского календаря результат может быть
 * некорректным
 *
 * Пример использования:
 * @code
 * if (is_leap_year(2024)) {
 *     printf("2024 is a leap year\n");
 * }
 * @endcode
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
 * @brief Парсит целое число из строки с проверкой переполнения
 *
 * Вспомогательная функция для безопасного парсинга целых чисел из строки.
 * Поддерживает:
 * - Необязательный знак (+/-)
 * - Проверку на допустимые цифры
 * - Контроль переполнения (включая INT_MIN/INT_MAX)
 * - Постепенное перемещение указателя по строке
 *
 * @param[in,out] str Указатель на указатель текущей позиции в строке (будет изменен)
 * @param[out] number Указатель для записи результата парсинга
 * @return 1 если парсинг успешен, 0 при ошибке (нечисловой символ/переполнение)
 *
 * @note Обрабатывает как положительные, так и отрицательные числа
 * @note Корректно работает с граничными значениями INT_MIN/INT_MAX
 * @note Пропускает только знак, но не пробелы (должны быть обработаны ранее)
 * @note Изменяет позицию указателя *str на первый символ после числа
 *
 * Пример использования:
 * @code
 * const char* ptr = "12345";
 * int value;
 * if (parse_number(&ptr, &value)) {
 *     printf("Parsed: %d\n", value);
 * }
 * @endcode
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
 * @brief Парсит числовое поле из CSV-строки.
 *
 * @param p             Указатель на текущую позицию в строке.
 * @param min_val       Минимальное допустимое значение.
 * @param max_val       Максимальное допустимое значение.
 * @param delimiter     Ожидаемый разделитель после поля.
 * @return int          Значение поля или -1 при ошибке.
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
 * @brief Проверяет, является ли строка CSV валидной.
 *
 * @param line          Строка из CSV-файла.
 * @param delimiter     Разделитель полей.
 * @param output        Указатель на структуру sensor для записи данных.
 * @return int          1 — если строка валидна, 0 — если нет.
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
    int temperature = parse_csv_field(&p, -99, 99, '\0');

    // Проверка успешности парсинга всех полей
    if (year == -1 || month == -1 || day == -1 || hour == -1 || minute == -1
        || temperature == -1)
    {
        return 0;
    }

    // Проверка дней в месяце (учитывая високосные годы)
    if (month == 2)
    {
        int max_day = is_leap_year(year) ? 29 : 28;
        if (day > max_day) return 0;
    }
    else if ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30)
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

    return 1;
}

/**
 * @brief Инициализирует структуру temp_stats.
 *
 * @param stats Указатель на структуру.
 * @param year Год для статистики.
 */
static void init_temp_stats(temp_stats* stats, uint16_t year)
{
    if (stats == NULL) return;

    memset(stats, 0, sizeof(temp_stats));
    stats->year = year;

    // Инициализация месячной статистики
    for (int i = 0; i < 12; i++)
    {
        // stats->monthly[i].avg_temp = 0;
        stats->monthly[i].min_temp = INT8_MAX;
        stats->monthly[i].max_temp = INT8_MIN;
        // stats->monthly[i].total_temp = 0;
        // stats->monthly[i].count = 0;
    }

    // Инициализация годовой статистики
    // stats->yearly.avg_temp = 0;
    stats->yearly.min_temp = INT8_MAX;
    stats->yearly.max_temp = INT8_MIN;
    // stats->yearly.total_temp = 0;
    // stats->yearly.count = 0;
}

/*----------------------------------------------------------------------------*/
/*                            Doubly Linked List (LIFO)                       */
/*----------------------------------------------------------------------------*/

/**
 * @brief Проверяет, является ли список пустым.
 *
 * @param head Указатель на голову списка.
 * @return true — если список пуст (head == NULL), иначе false.
 */
bool is_empty(node* head) { return head == NULL; }

/**
 * @brief Добавляет новый элемент в начало списка.
 *
 * @param head Указатель на указатель головы списка.
 * @param tail Указатель на указатель хвоста списка.
 * @param data Данные для добавления.
 */
void push(node** head, node** tail, sensor data)
{
    // 1. Создаём новый узел.
    // Для стандартов до С99 и С++
    node* new_node = (node*)malloc(sizeof(node)); // Выделяем память

    if (!new_node)
    {
        fprintf(stderr, "Memory allocation failed!\n");
        return;
    }
    // 2. Записываем в него данные.
    new_node->data = data; // Записываем значение
    // 3. Делаем его next равным текущей вершине (head).
    new_node->next = *head; // Новый узел указывает на старую вершину (head)
    //
    new_node->prev = NULL;

    // 4. Перемещаем head на новый узел.
    if (*head != NULL)
    {
        (*head)->prev = new_node;
    }
    else // Если список был пуст
    {
        *tail = new_node; // новый узел становится и хвостом
    }

    *head = new_node; // Теперь вершина — новый узел
}

/**
 * @brief Удаляет и возвращает элемент из начала списка.
 *
 * @param head Указатель на указатель головы списка.
 * @param tail Указатель на указатель хвоста списка.
 * @return sensor Данные удаленного узла или нулевая структура, если список пуст.
 */
sensor pop(node** head, node** tail)
{
    // sensor dummy = { 0 }; // Значение по умолчанию если стек пуст
    // 1. Проверяем, не пуст ли стек.
    if (is_empty(*head))
    {
        fprintf(stderr, "Stack underflow: cannot pop from an empty list.\n");
        return (sensor) { 0 }; // Возвращаем "пустые" данные
    }

    // 2. Запоминаем текущую вершину (temp = head).
    node* temp = *head;
    sensor popped_data = temp->data;

    // 3. Перемещаем head на следующий узел (head = head->next).
    *head = (*head)->next;
    if (*head != NULL)
    {
        (*head)->prev = NULL;
    }
    else
    {
        *tail = NULL; // Если список стал пустым, обнуляем tail
    }

    // 4. Возвращаем значение из temp и освобождаем память.
    free(temp);
    return popped_data;
}

/**
 * @brief Возвращает данные из начала списка без удаления.
 *
 * @param head Указатель на голову списка.
 * @return sensor Данные первого узла или нулевая структура, если список пуст.
 */
sensor peek(node* head)
{
    if (is_empty(head))
    {
        fprintf(stderr, "List is empty: nothing to peek.\n");
        return (sensor) { 0 };
    }
    return head->data;
}

/**
 * @brief Освобождает память, занятую списком.
 *
 * @param head Указатель на указатель головы списка.
 * @param tail Указатель на указатель хвоста списка.
 */
void free_list(node** head, node** tail)
{
    node* current = *head;
    while (current != NULL)
    {
        node* next = current->next;
        free(current);
        current = next;
    }
    *head = NULL;
    *tail = NULL; // Явное обнуление tail
}

/**
 * @brief Выводит содержимое списка.
 *
 * @param current Указатель на текущий узел (для рекурсивного обхода).
 * @param num Количество элементов для вывода (0 — все).
 * @param reverse Флаг обратного порядка вывода.
 */
void print_list(const node* current, int num, bool reverse)
{
    if (current == NULL)
    {
        printf("List is empty.\n");
        return;
    }

    printf("\nPrinting %d list values:\n", num);
    printf("-------------------------------------\n");
    printf("   №   | Date       | Time  | Temp  |\n");
    printf("-------+------------+-------+-------|\n");

    if (!reverse)
    {
        while (current->prev != NULL)
        {
            current = current->prev;
        }
    }

    int cnt = 0;
    while (current != NULL && (num <= 0 || cnt < num))
    {
        printf("%6d | %04d-%02d-%02d | %02d:%02d | %3d°C |\n",
            cnt + 1, //
            current->data.year, //
            current->data.month, //
            current->data.day, //
            current->data.hour, //
            current->data.minute, //
            current->data.temperature);

        current = reverse ? current->prev : current->next;
        cnt++;
    }

    if (current == NULL) printf("End of list.");
    printf("\n");
}

/*----------------------------------------------------------------------------*/
/*                                ВВОД ДАННЫХ                                 */
/*----------------------------------------------------------------------------*/

/**
 * @brief Загружает данные из CSV-файла в двунаправленный список.
 *
 * @param filename      Имя CSV-файла.
 * @param head          Указатель на голову списка.
 * @param tail          Указатель на хвост списка.
 * @param delimiter     Разделитель полей в CSV.
 * @param load_info     Структура для статистики загрузки.
 * @return size_t       Количество успешно загруженных записей.
 */
size_t load_from_csv(const char* filename, node** head, node** tail, char delimiter,
    load_stats* load_info)
{
    // Инициализация структуры статистики
    memset(load_info, 0, sizeof(load_stats));
    strncpy(load_info->filename, filename, sizeof(load_info->filename) - 1);
    load_info->filename[sizeof(load_info->filename) - 1] = '\0';

    // Всегда записываем ожидаемое имя лог-файла
    strncpy(load_info->logfile, LOG_FILENAME, sizeof(load_info->logfile) - 1);
    load_info->logfile[sizeof(load_info->logfile) - 1] = '\0';
    load_info->log_success = false; // Флаг успешности открытия лога

    // 1. Сначала пробуем открыть основной файл данных
    FILE* file = fopen(filename, "r");
    if (!file)
    {
        perror("Failed to open data file");
        return 0;
    }

    // 2. Затем открываем лог-файл
    FILE* log_file = fopen(LOG_FILENAME, "w");
    if (!log_file)
    {
        log_file = stderr;
        fprintf(log_file, "Warning: Could not open log file '%s'. Using stderr.\n",
            LOG_FILENAME);
    }
    else
    {
        load_info->log_success = true; // флаг успешности открытия лог файла
    }

    char line[32];
    sensor data;

    // Считываем данные
    while (fgets(line, sizeof(line), file))
    {
        load_info->total_lines++;

        // Удаление символов новой строки
        line[strcspn(line, "\r\n")] = '\0';

        // Пустые строки и комментарии
        if (line[0] == '\0' || line[0] == '#')
        {
            fprintf(log_file, "Line %zu: Empty line or comment - %s\n",
                load_info->total_lines, line);
            load_info->empty_lines++;
            continue;
        }

        // Валидация записи
        if (!is_valid_line(line, delimiter, &data))
        {
            fprintf(log_file, "Line %zu: Invalid data - %s\n", load_info->total_lines,
                line);
            load_info->invalid_values++;
            continue;
        }

        // Все проверки пройдены - записываем
        push(head, tail, data);
        load_info->valid_records++;
    }

    fclose(file); // звкрыть файл с данными
    if (log_file != stderr) fclose(log_file); // закрыть лог файл

    // Дополнительная информация в лог
    if (load_info->log_success)
    {
        FILE* log = fopen(LOG_FILENAME, "a");
        if (log)
        {
            fprintf(log, "=== Loading completed ===\n");
            fprintf(log, "Total records: %zu\n", load_info->valid_records);
            fprintf(log, "Errors: %zu\n", load_info->invalid_values);
            fclose(log);
        }
    }

    return load_info->valid_records;
}

/**
 * @brief Выводит статистику загрузки данных.
 *
 * @param load_info     Указатель на структуру load_stats.
 */
void print_load_stats(const load_stats* load_info)
{
    if (load_info == NULL)
    {
        fprintf(stderr, "Error: NULL load info pointer\n");
        return;
    }

    printf("\nFile Loading Statistics:\n");
    printf("--------------------------------------\n");
    printf(" Parameter          | Value\n");
    printf("--------------------|-----------------\n");
    printf(" Source file        | %s\n", load_info->filename);
    printf(" Total lines        | %zu\n", load_info->total_lines);
    printf(" Valid records      | %zu\n", load_info->valid_records);
    printf(" Empty lines        | %zu\n", load_info->empty_lines);
    printf(" Invalid values     | %zu\n", load_info->invalid_values);
    printf(" Log file           | %s\n", load_info->logfile);
    // printf("--------------------------------------\n");
    printf("\n");
}

/*----------------------------------------------------------------------------*/
/*                            СТАТИСТИКА                                      */
/*----------------------------------------------------------------------------*/

/**
 * @brief Вычисляет статистику температурных данных.
 *
 * @param head Указатель на голову списка с данными.
 * @return temp_stats Структура с рассчитанной статистикой.
 *
 * @note Для пустого списка возвращает структуру с нулевыми значениями.
 * @note Месяцы в массиве monthly: 0-11 (январь-декабрь).
 */
temp_stats calculate_stats(node* head)
{
    temp_stats stats = { 0 };

    if (head == NULL)
    {
        fprintf(stderr, "Warning: Empty list in calculate_stats()\n");
        return stats;
    }

    // Инициализация статистики годом первого элемента
    init_temp_stats(&stats, head->data.year);

    node* current = head;

    // Обработка данных
    while (current != NULL)
    {
        uint8_t month_idx = current->data.month - 1;
        int8_t temp = current->data.temperature;

        // Проверка согласованности года (все данные должны быть одного года)
        if (current->data.year != stats.year)
        {
            fprintf(stderr, "Warning: Inconsistent year %d (expected %d)\n",
                current->data.year, stats.year);
            current = current->next;
            continue;
        }

        // Месячная статистика
        stats.monthly[month_idx].total_temp += temp;
        stats.monthly[month_idx].count++;
        if (temp < stats.monthly[month_idx].min_temp)
        {
            stats.monthly[month_idx].min_temp = temp;
        }
        if (temp > stats.monthly[month_idx].max_temp)
        {
            stats.monthly[month_idx].max_temp = temp;
        }

        // Годовая статистика
        stats.yearly.total_temp += temp;
        stats.yearly.count++;
        if (temp < stats.yearly.min_temp) stats.yearly.min_temp = temp;
        if (temp > stats.yearly.max_temp) stats.yearly.max_temp = temp;

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

    // Расчет средней за год!
    if (stats.yearly.count > 0)
    {
        stats.yearly.avg_temp = (float)stats.yearly.total_temp / stats.yearly.count;
    }

    return stats;
}

/**
 * @brief Выводит статистику по месяцам в табличном формате.
 *
 * @param stats Указатель на структуру с данными.
 * @param month Номер месяца (1-12) или 0 для всех месяцев.
 *
 * @note Для месяцев без данных выводится "N/A".
 */
void print_monthly_stats(const temp_stats* stats, uint8_t month)
{
    if (stats == NULL)
    {
        fprintf(stderr, "Error: NULL stats pointer\n");
        return;
    }

    // Проверка корректности параметра month
    // if (month > 12)
    // {
    //     printf("Error: Invalid month number! Must be 0 (all months) or 1-12.\n");
    //     return;
    // }

    if (month == 0)
    {
        // Заголовок таблицы
        printf("\nMonthly Temperature Statistics:\n");
        printf("------------------------------------------------------\n");
        printf(" Year | Month | Count | Avg Temp | Max Temp | Min Temp\n");
        printf("------|-------|-------|----------|----------|---------\n");
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
        printf("\n");
    }
    else if (month >= 1 && month <= 12)
    {
        // Заголовок таблицы
        printf("\nTemperature statistics for month No. %d:\n", month);
        printf("------------------------------------------------------\n");
        printf(" Year | Month | Count | Avg Temp | Max Temp | Min Temp\n");
        printf("------|-------|-------|----------|----------|---------\n");
        // Вывод статистики за конкретный месяц
        int idx = month - 1;
        if (stats->monthly[idx].count > 0)
        {
            printf("%5d | %5d | %5d | %8.1f | %8d | %8d\n", stats->year, month,
                stats->monthly[idx].count, stats->monthly[idx].avg_temp,
                stats->monthly[idx].max_temp, stats->monthly[idx].min_temp);
        }
        else
        {
            printf("| %4d | %5s | %5s | %8s | %8s | %8s |\n", month, "N/A", "N/A",
                "N/A", "N/A", "N/A");
        }
        printf("\n");
    }
    else
    {
        fprintf(stderr, "Error: Invalid month %d\n", month);
    }
}

/**
 * @brief Выводит сводную годовую статистику.
 *
 * @param stats Указатель на структуру с данными.
 */
void print_yearly_stats(const temp_stats* stats)
{
    if (stats == NULL)
    {
        fprintf(stderr, "Error: NULL stats pointer\n");
        return;
    }
    if (stats->yearly.count > 0)
    {
        printf("Yearly statistics:\n");
        printf("------------------------------------------------\n");
        printf(" Year | Count  | Avg Temp | Max Temp | Min Temp\n");
        printf("------|--------|----------|----------|----------\n");
        printf("%5d   %5d   %7.1f   %8d   %8d\n",
            stats->year, // Год
            stats->yearly.count, // Общее количество измерений
            stats->yearly.avg_temp, // Средняя за год
            stats->yearly.max_temp, // Абсолютный максимум
            stats->yearly.min_temp); // Абсолютный минимум
        printf("\n");
    }
    else
    {
        printf("| %9s | %10s | %8s | %8s |\n", "N/A", "N/A", "N/A", "N/A");
    }
}

/*----------------------------------------------------------------------------*/
/*                                  СОРТИРОВКА                                */
/*----------------------------------------------------------------------------*/

/**
 * @brief Компаратор для сортировки по дате/времени.
 *
 * @param a Указатель на первую структуру sensor.
 * @param b Указатель на вторую структуру sensor.
 * @return int Результат сравнения:
 *             <0 если a < b
 *              0 если a == b
 *             >0 если a > b
 */
static int compare_by_date(const void* a, const void* b)
{
    /* Сортировка по возрастанию */
    // --------------------------//
    const sensor* sa = (const sensor*)a;
    const sensor* sb = (const sensor*)b;

    // Сравнение по годам
    if (sa->year != sb->year) return sa->year - sb->year;

    // Затем по месяцам
    if (sa->month != sb->month) return sa->month - sb->month;

    // Затем по дням
    if (sa->day != sb->day) return sa->day - sb->day;

    // Затем по часам
    if (sa->hour != sb->hour) return sa->hour - sb->hour;

    // И наконец по минутам
    return sa->minute - sb->minute;
}

/**
 * @brief Компаратор для сортировки по температуре.
 *
 * @param a Указатель на первую структуру sensor.
 * @param b Указатель на вторую структуру sensor.
 * @return int Результат сравнения (аналогично compare_by_date).
 */
static int compare_by_temp(const void* a, const void* b)
{
    /* Сортировка по возрастанию */
    // --------------------------//
    const sensor* sa = (const sensor*)a;
    const sensor* sb = (const sensor*)b;

    // Сначала сравниваем температуру
    int temp_diff = sa->temperature - sb->temperature;

    // При равной температуре сортируем по дате
    return (temp_diff != 0) ? temp_diff : compare_by_date(a, b);
}

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
void sort_list(node** head, node** tail, char criteria)
{
    if (head == NULL || *head == NULL || (*head)->next == NULL)
    {
        return; // Нет необходимости сортировать пустой или единичный элемент
    }

    // Подсчёт элементов
    size_t count = 0;
    node* current = *head;
    while (current != NULL)
    {
        count++;
        current = current->next;
    }

    // Выделение временного массива
    sensor* arr = (sensor*)malloc(count * sizeof(sensor));
    if (arr == NULL)
    {
        perror("Failed to allocate memory for sorting");
        return;
    }

    // Заполнение массива данными из списка
    current = *head;
    for (size_t i = 0; i < count; i++)
    {
        arr[i] = current->data;
        current = current->next;
    }

    // 2. Сортируем массив
    qsort(arr, count, sizeof(sensor),
        criteria == 'd' ? compare_by_date : compare_by_temp);

    // Очищаем старый список
    free_list(head, tail);

    // Заполнение отсортированными данными
    for (int i = count - 1; i >= 0; i--)
    {
        push(head, tail, arr[i]);
    }

    free(arr);
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
    // Специальный случай: вызов без аргументов
    if (argc == 1) return 2;

    // Обнуляем структуру
    memset(args, 0, sizeof(cmd_args));
    args->mode = MODE_NONE;

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
            case 'p': fprintf(stderr, "Error: Missing count after -p\n"); return -1;
            case 's': fprintf(stderr, "Error: Missing count after -s\n"); return -1;
            }
        }

        switch (arg[1])
        {
        case 'f':
            args->filename = argv[i + 1];
            args->mode |= MODE_FILE;
            i++; // Пропускаем следующий аргумент (значение)
            break;
        case 'm':
            sscanf(argv[i + 1], "%hhu", &args->month);
            args->mode |= MODE_MONTH;
            i++;
            break;
        case 'p':
            sscanf(argv[i + 1], "%hhu", &args->printdb);
            args->mode |= MODE_PRINT;
            i++;
            break;
        case 's':
            sscanf(argv[i + 1], "%c", &args->sort);
            args->mode |= MODE_SORT;
            i++;
            break;
        case 'h': return 1;
        default:
            fprintf(stderr, "Ошибка: неизвестная опция '-%c'\n", arg[1]);
            return -1;
        }
    }

    // Проверка обязательных параметров через флаги
    if (!(args->mode & MODE_FILE))
    {
        fprintf(stderr, "Ошибка: не указан входной файл (используйте -f)\n");
        return -1;
    }

    // Дополнительные проверки значений
    if ((args->mode & MODE_MONTH) && (args->month > 12))
    {
        fprintf(stderr, "Ошибка: некорректный месяц (должен быть 1-12)\n");
        return -1;
    }

    if ((args->mode & MODE_SORT) && (args->sort != 'd' && args->sort != 't'))
    {
        fprintf(stderr,
            "Ошибка: некорректный критерий сортировки (должен быть 'd' или 't')\n");
        return -1;
    }

    return 0;
}

/**
 * @brief Обрабатывает данные согласно указанному режиму работы
 *
 * @param head Указатель на голову списка
 * @param tail Указатель на хвост списка
 * @param args Параметры командной строки
 * @param load_info Статистика загрузки
 */
void process_data_mode(node* head, node* tail, cmd_args* args, load_stats* load_info)
{
    switch (args->mode)
    {
    case MODE_FILE: { // Только файл (-f)
        print_load_stats(load_info);
        temp_stats stats = calculate_stats(head);
        print_monthly_stats(&stats, 0);
        print_yearly_stats(&stats);
        break;
    }
    case MODE_FILE_MONTH: { // Файл + месяц (-f -m)
        temp_stats stats = calculate_stats(head);
        print_monthly_stats(&stats, args->month);
        break;
    }
    case MODE_FILE_PRINT: { // Файл + печать (-f -p)
        print_list(tail, args->printdb, true);
        break;
    }
    case MODE_FILE_SORT_PRINT: { // Файл + сортировка + печать (-f -s -p)
        sort_list(&head, &tail, args->sort);
        print_list(tail, args->printdb, false);
        break;
    }
    default: // Неизвестная комбинация
        fprintf(stderr, "Warning: Unknown mode combination (0x%X)\n", args->mode);
    }
}
/*----------------------------------------------------------------------------*/
/*                                                                            */
/*----------------------------------------------------------------------------*/