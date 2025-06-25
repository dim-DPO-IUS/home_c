#include "temp_api.h"

/*----------------------------------------------------------------------------*/
/*                            STATIC HELPER FUNCTIONS                         */
/*----------------------------------------------------------------------------*/

/**
 * @brief Convert date to integer representation for comparison
 * @param data Pointer to sensor data
 * @return Integer representation of the date (YYYYMMDDhhmm)
 */
unsigned int date_to_int(sensor_t* data)
{
    return data->year << 24 | data->month << 16 | data->day << 8
           | data->hour << 4 | data->minute;
}

/**
 * @brief Swap two sensor records
 * @param data Sensor data array
 * @param i First index
 * @param j Second index
 */
void changeIJ(sensor_t* data, int i, int j)
{
    sensor_t temp;
    temp = data[i];
    data[i] = data[j];
    data[j] = temp;
}

/**
 * @brief Generate random integer in range [min, max]
 * @param min Minimum value
 * @param max Maximum value
 * @return Random integer
 */
int random_int(int min, int max)
{
    return min + rand() % (max - min + 1);
}

/*----------------------------------------------------------------------------*/
/*                            STATISTICS FUNCTIONS                            */
/*----------------------------------------------------------------------------*/

void print_stats(sensor_t* data, size_t count, uint8_t month, uint16_t year)
{
    // Или month или year должны быть равны 0
    if(month + year == 0 || month * year != 0)
    {
        printf("month и year не могут быть оба равны 0 или оба НЕ равны 0\n");
        return;
    }

    int sum = 0, min = INT_MAX, max = INT_MIN;
    size_t entries = 0;

    // Calculate statistics
    for(size_t i = 0; i < count; i++)
    {
        if((month && data[i].month == month) || (year && data[i].year == year))
        {
            sum += data[i].temperature;
            min = (data[i].temperature < min) ? data[i].temperature : min;
            max = (data[i].temperature > max) ? data[i].temperature : max;
            entries++;
        }
    }

    // Print results
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

/*----------------------------------------------------------------------------*/
/*                            DATA MANIPULATION                               */
/*----------------------------------------------------------------------------*/

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

int add_records(sensor_t* data, int count)
{
    // Initialize random seed with current time
    srand(time(NULL));
    return generate_sensor_data(data, count);
}

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

int remove_by_index(sensor_t* data, int size, int index)
{
    if(index < 0 || index >= size)
    {
        fprintf(stderr, "Error: Index %d out of bounds [0, %d)\n", index, size);
        return size;
    }

    for(int i = index; i < size - 1; i++)
    {
        data[i] = data[i + 1];
    }

    return size - 1;
}

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

/*----------------------------------------------------------------------------*/
/*                            SORTING FUNCTIONS                               */
/*----------------------------------------------------------------------------*/

void sort_by_date(sensor_t* data, int n)
{
    for(int i = 0; i < n; ++i)
        for(int j = i; j < n; ++j)
            if(date_to_int(data + i) >= date_to_int(data + j))
                changeIJ(data, i, j);
}

void sort_by_t(sensor_t* data, int n)
{
    for(int i = 0; i < n; ++i)
        for(int j = i; j < n; ++j)
            if(data[i].temperature >= data[j].temperature) changeIJ(data, i, j);
}

/*----------------------------------------------------------------------------*/
/*                            DATA GENERATION                                 */
/*----------------------------------------------------------------------------*/

int generate_sensor_data(sensor_t* data, int count)
{
    if(data == NULL || count <= 0)
    {
        return 0;
    }

    srand(21);

    const int days_in_month[] =
        {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    for(int i = 0; i < count; i++)
    {
        data[i].year = random_int(2020, 2023);
        data[i].month = random_int(1, 12);
        data[i].day = random_int(1, days_in_month[data[i].month - 1]);
        data[i].hour = random_int(0, 23);
        data[i].minute = random_int(0, 59);
        data[i].temperature = random_int(-30, 35);
    }

    return count;
}

/*----------------------------------------------------------------------------*/
/*                            OUTPUT FUNCTIONS                                */
/*----------------------------------------------------------------------------*/

void print(sensor_t* data, int number)
{
    if(data == NULL || number <= 0)
    {
        printf("No data to display\n");
        return;
    }

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

/*----------------------------------------------------------------------------*/
/*                            COMMAND LINE PARSING                            */
/*----------------------------------------------------------------------------*/

int parse_arguments(int argc, char* argv[], cmd_args_t* args)
{
    // Обнуляем структуру
    memset(args, 0, sizeof(cmd_args_t));

    for(int i = 0; i < argc; i++)
    {
        char* arg = argv[i];

        // Пропускаем не-флаги (например, значения аргументов)
        if(arg[0] != '-') continue;

        // Проверяем, что после флага есть значение (если требуется)
        if(i + 1 >= argc || argv[i + 1][0] == '-')
        {
            switch(arg[1])
            {
            case 'f':
                fprintf(stderr, "Error: Missing filename after -f\n");
                return -1;
            case 'm':
                fprintf(stderr, "Error: Missing month after -m\n");
                return -1;
            case 'y':
                fprintf(stderr, "Error: Missing year after -y\n");
                return -1;
            case 'p':
                fprintf(stderr, "Error: Missing count after -p\n");
                return -1;
            }
        }

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
            printf(HELP_MSG, argv[0]);
            return 1;
        default:
            fprintf(stderr, "Ошибка: неизвестная опция '-%c'\n", arg[1]);
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