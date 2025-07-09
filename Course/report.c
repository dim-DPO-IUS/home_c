#include "temp_function.h"

#define DEBUG_MODE 0

int main(int argc, char* argv[])
{
    node* head = NULL;
    node* tail = NULL;

#if DEBUG_MODE
    // ======================================================================
    load_stats load_info;
    load_from_csv("temperature_big.csv", &head, &tail, ';', &load_info);
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
        if (load_from_csv(args.filename, &head, &tail, ';', &load_info))
        {
            if (!args.month && !args.printdb && !args.sort)
            {
                print_load_stats(&load_info); // Статистика загрузки
                temp_stats stats
                    = calculate_stats(head); // Счет статистики температур
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
        temp_stats stats = calculate_stats(head);
        print_monthly_stats(&stats, args.month);
        printf("\n");
    }

    // -------------- Сортировка ------------------------//
    if (args.sort == 'd' || args.sort == 't')
    {
        sort_list(&head, &tail, args.sort);
    }

    // --------------Печать (в прямом порядке)-----------//
    if (args.printdb)
    {
        // если сортировка, то выведет по возрастанию - как надо
        // если нет сортировки, то выведет файл в обратном порядке
        print_list(head, -1, false);

        // print_list(tail, args.printdb, true); // в прямом порядке
        // print_list(tail, args.printdb, false); // в обратном порядке
    }

#endif // DEBUG_MODE

    // -------------- Очистка стека (если нужно) --------//
    free_list(&head, &tail);

    return 0;
}