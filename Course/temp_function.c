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
 * @brief Парсит и валидирует поле CSV-строки
 *
 * Вспомогательная функция для парсинга отдельных полей CSV-строки.
 * Выполняет:
 * - Пропуск пробелов до и после значения
 * - Парсинг числового значения
 * - Проверку на соответствие допустимому диапазону
 * - Проверку наличия корректного разделителя после значения
 *
 * @param[in,out] p Указатель на указатель текущей позиции в строке (будет изменен)
 * @param[in] min_val Минимально допустимое значение поля
 * @param[in] max_val Максимально допустимое значение поля
 * @param[in] delimiter Ожидаемый символ-разделитель после поля
 * @return Значение поля (>=0) при успешном парсинге, -1 при ошибке
 *
 * @note Поддерживает пробелы до и после числового значения
 * @note Для последнего поля в строке можно передать delimiter='\0'
 * @note Изменяет указатель *p, перемещая его на следующее поле
 * @note Использует вспомогательную функцию parse_number() для парсинга чисел
 *
 * Пример использования:
 * @code
 * const char* ptr = "2023,12,31";
 * int year = parse_csv_field(&ptr, 2000, 2100, ',');
 * @endcode
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
 * @brief Проверяет валидность строки CSV-файла и извлекает данные
 *
 * Функция парсит строку CSV-файла, проверяет соответствие формату и
 * корректность значений. При успешной проверке заполняет структуру sensor.
 *
 * @param[in] line Строка CSV-файла для парсинга
 * @param[in] delimiter Символ-разделитель полей в CSV
 * @param[out] data Указатель на структуру sensor для записи данных
 * @return true если строка валидна и данные извлечены успешно,
 *         false если строка не соответствует формату или содержит некорректные
 * значения
 *
 * @note Ожидаемый формат строки: год,месяц,день,час,минута,температура
 * @note Проверяет:
 *       - корректность количества полей
 *       - допустимость значений даты/времени
 *       - диапазон температур (INT8_MIN..INT8_MAX)
 * @note Для некорректных строк выводит сообщение об ошибке в stderr
 *
 * Пример корректной строки:
 * @code
 * 2023,12,31,23,59,15
 * @endcode
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
 * @brief Инициализирует структуру temp_stats начальными значениями
 *
 * Функция устанавливает начальные значения для всех полей структуры temp_stats:
 * - Устанавливает год наблюдений
 * - Инициализирует массив месячной статистики (12 месяцев)
 * - Инициализирует структуру годовой статистики
 *
 * @param[out] stats Указатель на структуру temp_stats для инициализации
 * @param[in] year Год наблюдений, который будет записан в статистику
 *
 * @note Для минимальных температур устанавливается INT8_MAX
 * @note Для максимальных температур устанавливается INT8_MIN
 * @note Все счетчики (count) и суммарные температуры (total_temp) обнуляются
 * @note Средние температуры (avg_temp) инициализируются нулями
 * @warning Для корректной работы последующих вычислений должна вызываться первой
 *          перед заполнением структуры статистики
 *
 * Пример использования:
 * @code
 * temp_stats stats;
 * init_temp_stats(&stats, 2023);
 * @endcode
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

/**
 * @brief Функция сравнения двух структур sensor по дате и времени
 *
 * Используется как компаратор для qsort() и других функций сортировки.
 * Сравнивает даты и время двух структур sensor в следующем порядке приоритетов:
 * 1. Год (year)
 * 2. Месяц (month)
 * 3. День (day)
 * 4. Час (hour)
 * 5. Минута (minute)
 *
 * @param[in] a Указатель на первую структуру sensor
 * @param[in] b Указатель на вторую структуру sensor
 * @return
 *      - Отрицательное число, если дата a раньше даты b
 *      - Ноль, если даты полностью совпадают
 *      - Положительное число, если дата a позже даты b
 *
 * @note Функция реализует лексикографическое сравнение дат (по возрастанию)
 * @note Для сортировки по убыванию можно инвертировать знак возвращаемого значения
 */
static int compare_by_date(const void* a, const void* b)
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
 * @brief Функция сравнения двух структур sensor по температуре
 *
 * Используется как компаратор для qsort() и других функций сортировки.
 * Сравнивает значения температуры двух структур sensor.
 *
 * @param[in] a Указатель на первую структуру sensor
 * @param[in] b Указатель на вторую структуру sensor
 * @return
 *      - Отрицательное число, если температура a < температуры b
 *      - Ноль, если температуры равны
 *      - Положительное число, если температура a > температуры b
 *
 * @note Применяется для сортировки по возрастанию температуры.
 */
static int compare_by_temp(const void* a, const void* b)
{
    sensor* s1 = (sensor*)a;
    sensor* s2 = (sensor*)b;

    return s1->temperature - s2->temperature;
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
void push(node** head, node** tail, sensor data)
{
    // 1. Создаём новый узел.
    // Для стандартов до С99 и С++
    node* new_node = (node*)malloc(sizeof(node)); // Выделяем память

    if (!new_node)
    {
        printf("Memory error!\n"); // Если память не выделилась
        return;
    }
    // 2. Записываем в него данные.
    new_node->data = data; // Записываем значение
    // 3. Делаем его next равным текущей вершине (head).
    new_node->next = *head; // Новый узел указывает на старую вершину (head)
    //
    new_node->prev = NULL;

    // 4. Перемещаем top на новый узел.
    if (*head != NULL)
    {
        (*head)->prev = new_node;
    }

    *head = new_node; // Теперь вершина — новый узел

    if (*tail == NULL)
    {
        *tail = new_node;
    }
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
sensor pop(node** head, node** tail)
{
    sensor dummy = { 0 }; // Значение по умолчанию если стек пуст
    // 1. Проверяем, не пуст ли стек.
    if (*head == NULL)
    {
        printf("Stack underflow!\n");
        return dummy; // Возвращаем "пустую" структуру
    }
    // 2. Запоминаем текущую вершину (temp = head).
    node* temp = *head;
    sensor popped = temp->data;
    // 3. Перемещаем top на следующий узел (top = top->next).
    *head = (*head)->next;
    if (*head != NULL)
    {
        (*head)->prev = NULL;
    }
    else
    {
        *tail = NULL;
    }
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
 * @brief Освобождает память, занятую стеком
 *
 * Функция последовательно удаляет все элементы стека, начиная с вершины,
 * и освобождает выделенную под них память. После выполнения функции
 * стек становится пустым, а указатель на вершину стека (top) устанавливается в NULL.
 *
 * @param[in,out] top Указатель на указатель вершины стека
 *
 * @note Использует функцию pop() для удаления элементов
 * @note Безопасно вызывать для уже пустого стека
 * @note После выполнения функции стек полностью очищается
 *
 * Пример использования:
 * @code
 * node* stack = NULL;
 * // ... операции со стеком ...
 * free_stack(&stack); // полная очистка стека
 * @endcode
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
    *tail = NULL;
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
void print_list(const node* current, int num, bool reverse)
{
    if (current == NULL)
    {
        puts("List is empty.\n");
        return;
    }

    int cnt = 0;
    while (current != NULL && (num <= 0 || cnt < num))
    {
        printf("%04d-%02d-%02d %02d:%02d %3d°C\n", current->data.year,
            current->data.month, current->data.day, current->data.hour,
            current->data.minute, current->data.temperature);

        current = reverse ? current->prev : current->next;
        cnt++;
    }

    if (current == NULL) printf("NULL\n");
}

/*----------------------------------------------------------------------------*/
/*                                ВВОД ДАННЫХ                                 */
/*----------------------------------------------------------------------------*/

/**
 * @brief Загружает данные из CSV-файла в стек и собирает статистику загрузки
 *
 * Функция читает файл построчно, парсит записи о температуре и загружает их в стек.
 * В процессе загрузки собирается статистика:
 * - Общее количество строк в файле
 * - Количество пустых строк и строк-комментариев
 * - Количество строк с некорректными данными
 * - Количество успешно загруженных записей
 *
 * @param[in] filename Путь к CSV-файлу для загрузки
 * @param[out] top Указатель на указатель вершины стека (данные будут добавлены в
 * стек)
 * @param[in] delimiter Разделитель полей в CSV-файле
 * @param[out] load_info Указатель на структуру для сбора статистики загрузки
 * @return Количество успешно загруженных записей (valid_records)
 *
 * @note Формат CSV-файла должен соответствовать структуре sensor
 * @note Строки, начинающиеся с '#' считаются комментариями
 * @note Пустые строки пропускаются (учитываются в статистике)
 * @note Для валидации строк используется функция is_valid_line()
 * @note В случае ошибки открытия файла возвращает 0 и выводит сообщение об ошибке
 * @warning Максимальная длина строки ограничена 255 символами
 * @warning Имя файла в статистике обрезается до FILENAME_MAX-1 символов
 *
 * Пример использования:
 * @code
 * node* stack = NULL;
 * load_stats stats;
 * size_t loaded = load_from_csv("data.csv", &stack, ',', &stats);
 * printf("Loaded %zu valid records\n", loaded);
 * @endcode
 */

size_t load_from_csv(const char* filename, node** head, node** tail, char delimiter,
    load_stats* load_info)
{
    // Инициализация статистики
    memset(load_info, 0, sizeof(load_stats));
    // Запишем имя файла
    strncpy(load_info->filename, filename, sizeof(load_info->filename) - 1);
    load_info->filename[sizeof(load_info->filename) - 1] = '\0';

    // Открываем файл журнала ошибок в режиме "w" (перезапись)
    FILE* log_file = fopen(LOG_FILENAME, "w"); // "w" - пересоздаёт файл
    if (!log_file)
    {
        perror("Failed to create log file");
        log_file = stderr; // Fallback на stderr, если не удалось открыть файл
    }
    else
    {
        // Запишем имя лог-файла
        strncpy(load_info->logfile, LOG_FILENAME, sizeof(load_info->logfile) - 1);
        load_info->logfile[sizeof(load_info->logfile) - 1] = '\0';
    }

    // Открываем файл данных
    FILE* file = fopen(filename, "r");
    if (!file)
    {
        fprintf(log_file, "Failed to open input file: %s\n", filename);
        perror("Failed to open file");
        // Закрыть логфайл
        if (log_file != stderr) fclose(log_file);

        return 0;
    }

    char line[32];
    sensor data;

    // Считываем данные
    while (fgets(line, sizeof(line), file))
    {
        load_info->total_lines++;
        line[strcspn(line, "\r\n")] = '\0'; // Удаление символов новой строки

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

    return load_info->valid_records;
}

/**
 * @brief Выводит статистику загрузки данных в удобочитаемом формате
 *
 * Функция форматирует и выводит на стандартный вывод (stdout) статистику
 * загрузки данных, включая:
 * - Имя обработанного файла
 * - Общее количество обработанных строк
 * - Количество пустых строк и комментариев
 * - Количество успешно загруженных записей
 * - Количество строк с неверным форматом
 * - Количество строк с некорректными значениями
 *
 * @param[in] load_info Указатель на структуру со статистикой загрузки
 *
 * @note Формат вывода:
 *
 * File loading statistics:
 * --------------------------------
 * File Name:             data.csv
 * Total lines processed: 100
 * Empty lines/comments:  5
 * Valid records:         90
 * Invalid format:        3
 * Invalid values:        2
 * --------------------------------
 *
 * @note Все значения выводятся в виде целых чисел (size_t)
 * @note Для вывода используется форматированная таблица с выравниванием
 */
void print_load_stats(const load_stats* load_info)
{
    printf("--------------------------------\n");
    printf("File loading statistics:\n");
    printf("--------------------------------\n");
    printf("File Name:             %s\n", load_info->filename);
    printf("Total lines processed: %zu\n", load_info->total_lines);
    printf("Empty lines/comments:  %zu\n", load_info->empty_lines);
    printf("Valid records:         %zu\n", load_info->valid_records);
    printf("Invalid format:        %zu\n", load_info->invalid_format);
    printf("Invalid values:        %zu\n", load_info->invalid_values);
    printf("LogFile:               %s\n", load_info->logfile);
    printf("\n");
}

/*----------------------------------------------------------------------------*/
/*                            СТАТИСТИКА                                      */
/*----------------------------------------------------------------------------*/

/**
 * @brief Вычисляет статистику температурных данных из стека записей
 *
 * Функция анализирует данные в стеке и рассчитывает:
 * - Месячную статистику (для каждого месяца отдельно)
 * - Годовую статистику (агрегированные данные за весь год)
 *
 * @param[in] top Указатель на вершину стека с температурными данными
 * @return temp_stats Структура с рассчитанной статистикой
 *
 * @note Возвращает нулевую структуру, если стек пуст
 * @note Для каждого месяца рассчитывает:
 *       - количество измерений
 *       - суммарную температуру
 *       - среднюю температуру
 *       - минимальную температуру
 *       - максимальную температуру
 * @note Для годовой статистики используются аналогичные показатели
 * @note Средние значения рассчитываются только при наличии данных (count > 0)
 * @warning При пустом стеке выводится предупреждающее сообщение
 * @warning Нумерация месяцев в массиве monthly: 0-11 (январь-декабрь)
 *
 * Пример использования:
 * @code
 * temp_stats stats = calculate_stats(sensor_stack);
 * print_yearly_stats(&stats);
 * @endcode
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
 * @brief Выводит месячную статистику температурных показателей в виде таблицы
 *
 * Функция выводит статистику температур для указанного месяца или для всех месяцев,
 * если в качестве параметра month передан 0. Вывод включает:
 * - Год наблюдений
 * - Номер месяца
 * - Количество измерений
 * - Среднюю температуру
 * - Максимальную температуру
 * - Минимальную температуру
 *
 * @param[in] stats Указатель на структуру temp_stats с данными статистики
 * @param[in] month Номер месяца (1-12) или 0 для вывода всех месяцев
 *
 * @note Формат вывода:
 * ------------------------------------------------------
 *  Year | Month | Count | Avg Temp | Max Temp | Min Temp
 * ------|-------|-------|----------|----------|---------
 *  2023 |     1 |   31  |    -5.2  |      12  |     -15
 *
 * @note При month=0 выводится статистика только для месяцев с ненулевым количеством
 * измерений
 * @note При отсутствии данных для указанного месяца выводится соответствующее
 * сообщение
 * @note Для некорректного номера месяца (>12) выводится сообщение об ошибке
 * @warning Нумерация месяцев в выводе: 1-12 (в структуре индексы 0-11)
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
 * @brief Выводит годовую статистику температурных показателей в виде таблицы
 *
 * Функция форматирует и выводит на стандартный вывод статистику за год
 * в виде читаемой таблицы с заголовками. Вывод включает:
 * - Год наблюдений
 * - Общее количество измерений
 * - Среднегодовую температуру
 * - Максимальную зафиксированную температуру
 * - Минимальную зафиксированную температуру
 *
 * @param[in] stats Указатель на структуру temp_stats, содержащую статистические
 * данные
 *
 * @note Формат вывода:
 * -----------------------------------------------
 *  Year | Count | Avg Temp | Max Temp | Min Temp
 * ------|-------|----------|----------|----------
 *  2023 |   365 |     15.2 |       35 |       -5
 *
 * @note Для среднего значения используется формат вывода с 1 десятичным знаком
 * @note Для экстремальных значений используется целочисленный формат
 */
void print_yearly_stats(const temp_stats* stats)
{
    printf("\nYearly statistics:\n");
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

/*----------------------------------------------------------------------------*/
/*                                  СОРТИРОВКА                                */
/*----------------------------------------------------------------------------*/

/**
 * @brief Сортирует стек записей по заданному критерию
 *
 * Функция извлекает все элементы из стека во временный массив, сортирует его
 * с помощью стандартной функции qsort(), затем возвращает элементы обратно в стек.
 * При этом элементы помещаются в обратном порядке, чтобы верхний элемент стека
 * соответствовал первому элементу в отсортированном массиве.
 *
 * @param[in,out] top Указатель на вершину стека
 * @param[in] load_info Структура с информацией о загруженных данных, содержащая
 *                      количество валидных записей (valid_records)
 * @param[in] td Критерий сортировки:
 *               - 'd' - сортировка по дате (использует compare_by_date)
 *               - 't' - сортировка по температуре (использует compare_by_temp)
 *
 * @note Размер временного массива определяется полем load_info.valid_records
 * @note После выполнения функции стек будет содержать те же элементы,
 *       но в отсортированном порядке (верхний элемент - первый в отсортированном
 * массиве)
 */
void sort_list(node** head, node** tail, char td)
{
    if (*head == NULL || (*head)->next == NULL) return;

    // Подсчёт элементов
    int count = 0;
    node* temp = *head;
    while (temp != NULL)
    {
        count++;
        temp = temp->next;
    }

    // 1. Извлекаем все элементы в массив
    sensor* arr = (sensor*)malloc(count * sizeof(sensor));
    temp = *head;
    for (int i = 0; i < count; i++)
    {
        arr[i] = temp->data;
        temp = temp->next;
    }

    // 2. Сортируем массив
    qsort(arr, count, sizeof(sensor), td == 'd' ? compare_by_date : compare_by_temp);
    // Очистка списка
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
    // Вызов без аргументов
    if (argc == 1)
    {
        printf(START_MSG);
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
        case 'p': sscanf(argv[i + 1], "%hhu", &args->printdb); break;
        case 's': sscanf(argv[i + 1], "%c", &args->sort); break;
        case 'h': printf(HELP_MSG); return 1;
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