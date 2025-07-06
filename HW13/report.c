#include "temp_function.h"

#define DEBUG_MODE 0

int main(int argc, char* argv[])
{
    node* top = NULL;

#if DEBUG_MODE
    // ======================================================================
    load_stats load_info;
    load_from_csv("temperature_big.csv", &top, ';', &load_info);
    print_load_stats(&load_info);
    // ======================================================================
#else
    // -------------- Аргументы командной строки ---------//
    cmd_args args;
    int result = parse_arguments(argc, argv, &args);
    if (result == -1)
    {
        return 1;
    }
    else if (result == 1)
    {
        return 0;
    }

    // -------------- Загрузка из файла -----------------//
    load_stats load_info;
    if (args.filename) // имя файла
    {
        printf("------------------------------------------------------\n");
        if (load_from_csv(args.filename, &top, ';', &load_info))
        {
            if (!args.month && !args.printdb && !args.sort && !args.year)
            {
                print_load_stats(&load_info); // Статистика загрузки
                temp_stats stats = calculate_stats(top); // Счет статистики температур
                print_monthly_stats(&stats, 0); // Все месяцы
                print_yearly_stats(&stats); // Годовая статистика
            }
        }
        else
        {
            printf("Нет валидных данных\n");
        }
    }

    // -------------- Статистика за месяц ---------------//
    if (args.month)
    {
        temp_stats stats = calculate_stats(top);
        print_monthly_stats(&stats, args.month);
        printf("\n");
    }

#endif // DEBUG_MODE

    // -------------- Очистка стека (если нужно) --------//
    free_stack(&top);

    return 0;
}