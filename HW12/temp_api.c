#include "temp_api.h"

// Статистика ИЛИ по месяцу ИЛИ по году
// Или month или year должны быть равны 0
void print_stats(sensor_t* data, size_t count, uint8_t month, uint16_t year)
{
    if(month + year == 0 || month * year != 0)
    {
        printf("month и year не могут быть оба равны 0 или оба НЕ равны 0\n");
        return;
    }

    int sum = 0, min = INT_MAX, max = INT_MIN;
    size_t entries = 0;

    for(size_t i = 0; i < count; i++)
    {
        if((month && data[i].month == month) || (year && data[i].year == year))
        {
            sum += data[i].temperature;
            if(data[i].temperature < min)
                min = data[i].temperature;
            if(data[i].temperature > max)
                max = data[i].temperature;
            entries++;
        }
    }

    if(entries > 0)
    {
        printf("%s %02d:\n", month ? "Month" : "Year", month ? month : year);
        printf("  Avg: %.2f°C\n", (float)sum / entries);
        printf("  Min: %d°C\n", min);
        printf("  Max: %d°C\n", max);
    }
    else
    {
        printf("No data for %s %02d:\n",
               month ? "Month" : "Year",
               month ? month : year);
    }
}

// Добавление одной записи. Создание массива структур
void add_record(sensor_t* data,
                int number,
                uint16_t year,
                uint8_t month,
                uint8_t day,
                uint8_t hour,
                uint8_t minute,
                int8_t t)
{
    data[number].year = year;
    data[number].month = month;
    data[number].day = day;
    data[number].hour = hour;
    data[number].minute = minute;
    data[number].temperature = t;
}

// Добавление набора записей
int add_records(sensor_t* data, int count)
{
    // int counter = 0;
    // add_record(data, counter++, 2021, 9, 16, 12, 30, 9);
    // add_record(data, counter++, 2022, 9, 2, 12, 30, -10);
    // add_record(data, counter++, 2021, 1, 7, 12, 30, 8);
    // add_record(data, counter++, 2021, 9, 5, 12, 30, 1);
    // add_record(data, counter++, 2022, 9, 3, 12, 30, -20);
    //--------------------------------------------------------
    //
    // Добавление случайного набора из 20 записей
    // Инициализация генератора случайных чисел
    srand(time(NULL));
    // Генерация данных
    int counter = generate_sensor_data(data, count);
    return counter;
}

// Поиск индекса записи
int find_index(sensor_t data[],
               int size,
               uint16_t year,
               uint8_t month,
               uint8_t day,
               uint8_t hour,
               uint8_t minute)
{
    for(int i = 0; i < size; i++)
    {
        if(data[i].year == year && data[i].month == month && data[i].day == day
           && data[i].hour == hour && data[i].minute == minute)
        {
            return i;
        }
    }
    return -1;
}

// Удаление по индексу (возвращает новый размер)
int remove_by_index(sensor_t* data, int size, int index)
{
    if(index < 0 || index >= size)
    {
        printf("Error: Invalid index\n");
        return size;
    }

    for(int i = index; i < size - 1; i++)
    {
        data[i] = data[i + 1];
    }

    return size - 1;
}

// Удаление по дате (возвращает новый размер)
int remove_by_date(sensor_t* data,
                   int size,
                   uint16_t year,
                   uint8_t month,
                   uint8_t day)
{
    int i = 0;
    while(i < size)
    {
        if(data[i].year == year && data[i].month == month && data[i].day == day)
        {
            size = remove_by_index(data, size, i);
        }
        else
        {
            i++;
        }
    }
    return size;
}

// Печать массива записей
void print(sensor_t* data, int number)
{
    // printf("===================================\n");
    // for(int i = 0; i < number; i++)
    //     printf("%04d-%02d-%02d %02d:%02d t=%3d\n",
    //            data[i].year,
    //            data[i].month,
    //            data[i].day,
    //            data[i].hour,
    //            data[i].minute,
    //            data[i].temperature);
    //------------------------------------------------
    printf("No.  Date       Time  Temp\n");
    printf("----------------------------\n");
    for(int i = 0; i < number; i++)
    {
        printf("%2d. %04d-%02d-%02d %02d:%02d %3d°C\n",
               i + 1,
               data[i].year,
               data[i].month,
               data[i].day,
               data[i].hour,
               data[i].minute,
               data[i].temperature);
    }
}

// Меняет местами data[i] <--> data[j]
void changeIJ(sensor_t* data, int i, int j)
{
    sensor_t temp;
    temp = data[i];
    data[i] = data[j];
    data[j] = temp;
}

// Упорядочить по дате
void sort_by_date(sensor_t* data, int n)
{
    for(int i = 0; i < n; ++i)
        for(int j = i; j < n; ++j)
            if(date_to_int(data + i) >= date_to_int(data + j))
                changeIJ(data, i, j);
}

// Упорядочить по температуре по неубыванию
void sort_by_t(sensor_t* data, int n)
{
    for(int i = 0; i < n; ++i)
        for(int j = i; j < n; ++j)
            if(data[i].temperature >= data[j].temperature)
                changeIJ(data, i, j);
}

//
unsigned int date_to_int(sensor_t* data)
{
    return data->year << 16 | data->month << 8 | data->day;
}

// Функция для генерации случайного числа в диапазоне
int random_int(int min, int max)
{
    return min + rand() % (max - min + 1);
}

// Генератор записей (возвращает количество сгенерированных записей)
int generate_sensor_data(sensor_t* data, int count)
{
    if(data == NULL || count <= 0)
    {
        return 0;
    }

    // Фиксируем seed для повторяемости
    srand(21);

    for(int i = 0; i < count; i++)
    {
        // Генерация года (2020-2023)
        data[i].year = random_int(2020, 2023);

        // Генерация месяца (1-12)
        data[i].month = random_int(1, 12);

        // Генерация дня с учетом месяца
        int max_day = 30;
        if(data[i].month == 2)
        {
            max_day = 28; // Без учета високосных годов
        }
        else if(data[i].month == 1 || data[i].month == 3 || data[i].month == 5
                || data[i].month == 7 || data[i].month == 8
                || data[i].month == 10 || data[i].month == 12)
        {
            max_day = 31;
        }
        data[i].day = random_int(1, max_day);

        // Генерация времени
        data[i].hour = random_int(0, 23);
        data[i].minute = random_int(0, 59);

        // Генерация температуры (-30..+35)
        data[i].temperature = random_int(-30, 35);
    }

    return count;
}

// Парсер аргументов командной строки
// Возвращает:
//  1: при вызове справки
//  -1: при ошибке
int parse_arguments(int argc, char* argv[], cmd_args_t* args)
{
    // Установка значений по умолчанию
    args->filename = NULL;
    args->month = 0;
    args->year = 0;
    args->printdb = 0;
    // args->debug_mode = 0;
    // args->seed = 42;

    for(int i = 0; i < argc; i++)
    {
        char* arg = argv[i];

        if(arg[0] != '-')
        {
            continue; // Пропускаем не-флаги (например, значения аргументов)
        }

        // Проверяем, что после флага есть значение (если требуется)
        if(i + 1 >= argc || argv[i + 1][0] == '-')
        {
            switch(arg[1])
            {
            case 'f':
                fprintf(stderr, "Ошибка: после -f требуется указать файл\n");
                return -1;
            case 'm':
                fprintf(stderr,
                        "Ошибка: после -m требуется указать месяц (1-12)\n");
                return -1;
            case 'y':
                fprintf(stderr, "Ошибка: после -y требуется указать год\n");
                return -1;
            case 'p':
                fprintf(stderr, "Ошибка: после -p требуется указать число\n");
                return -1;
            }
        }
        // -------------------------------------
        switch(arg[1])
        {
        case 'f':
            args->filename = argv[i + 1];
            break;
        case 'm':
            sscanf(argv[i + 1], "%hhu", &args->month);
            break;
        case 'y':
            sscanf(argv[i + 1], "%hu", &args->year);
            break;
        case 'p':
            sscanf(argv[i + 1], "%hhu", &args->printdb);
            break;

        case 'h':
            printf(HELP_MSG, argv[0]); // Используем глобальную строку
            return 1;

        default:
            fprintf(stderr, "Ошибка: неизвестная опция '-%c'\n", argv[i][1]);
            return -1;
        }
    }
    // Проверка обязательных параметров
    // if(args->filename == NULL)
    // {
    //     fprintf(stderr, "Ошибка: не указан входной файл (используйте -f)\n");
    //     return -1;
    // }

    return 0;
}