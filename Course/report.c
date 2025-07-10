#include "temp_function.h"

int main(int argc, char* argv[])
{
    node *head = NULL, *tail = NULL;
    cmd_args args = { 0 };
    load_stats load_info = { 0 };
    int ret_code = 0; // Код возврата по умолчанию

    // Парсинг аргументов
    int parse_result = parse_arguments(argc, argv, &args);
    if (parse_result == 2)
    {
        printf(START_MSG);
    }
    else if (parse_result == 1)
    {
        printf(HELP_MSG);
    }
    else if (parse_result == -1)
    {
        ret_code = 1;
    }
    else if (!load_from_csv(args.filename, &head, &tail, ';', &load_info))
    {
        printf("No valid data found in file\n");
        ret_code = 1;
    }
    else
    {
        // Основная логика обработки
        if (args.sort)
        {
            sort_list(&head, &tail, args.sort);
        }

        if (args.month)
        {
            temp_stats stats = calculate_stats(head);
            print_monthly_stats(&stats, args.month);
        }
        else if (args.printdb)
        {
            print_list(tail, args.printdb, !args.sort);
        }
        else
        {
            print_load_stats(&load_info);
            temp_stats stats = calculate_stats(head);
            print_monthly_stats(&stats, 0);
            print_yearly_stats(&stats);
        }
    }

    // /* Main processing - only if parse_result == 0 */
    // if (!args.filename)
    // {
    //     free_list(&head, &tail);
    //     return 1;
    // }

    // if (!load_from_csv(args.filename, &head, &tail, ';', &load_info))
    // {
    //     printf("No valid data found in file\n");
    //     free_list(&head, &tail);
    //     return 1;
    // }

    // /* Default output when no specific options */
    // if (!args.month && !args.printdb && !args.sort)
    // {
    //     print_load_stats(&load_info);
    //     temp_stats stats = calculate_stats(head);
    //     print_monthly_stats(&stats, 0);
    //     print_yearly_stats(&stats);
    // }

    // /* Monthly stats */
    // if (args.month)
    // {
    //     temp_stats stats = calculate_stats(head);
    //     print_monthly_stats(&stats, args.month);
    // }

    // /* Sorting */
    // if (args.sort == 'd' || args.sort == 't')
    // {
    //     sort_list(&head, &tail, args.sort);
    // }

    // /* Printing - improved logic */
    // if (args.printdb)
    // {
    //     bool reverse_order = !args.sort; // Reverse if not sorted
    //     print_list(tail, args.printdb, reverse_order);
    // }

    // -------------- Очистка стека (если нужно) --------//
    free_list(&head, &tail);

    return ret_code;
}