#include "temp_function.h"

#define DEBUG_MODE 0

int main(int argc, char* argv[])
{
    node* head = NULL;
    node* tail = NULL;

#if DEBUG_MODE
    // ======================================================================
    /* Debug mode - fixed test file processing */
    load_stats load_info;
    if (load_from_csv("temperature_big.csv", &head, &tail, ';', &load_info))
    {
        print_load_stats(&load_info);
    }
    else
    {
        fprintf(stderr, "Debug mode: Failed to load test file\n");
        free_list(&head, &tail);
        return 1;
    }
    // ======================================================================
#else
    /* Parse Arguments */
    cmd_args args;
    switch (parse_arguments(argc, argv, &args))
    {
    case -1: // Error in arguments
        free_list(&head, &tail);
        return 1;
    case 1: // Help message shown
        free_list(&head, &tail);
        return 0;
    }

    /* File loading */
    if (args.filename)
    {
        load_stats load_info;
        if (load_from_csv(args.filename, &head, &tail, ';', &load_info))
        {
            /* Default output when no specific options */
            if (!args.month && !args.printdb && !args.sort)
            {
                print_load_stats(&load_info);
                temp_stats stats = calculate_stats(head);
                print_monthly_stats(&stats, 0);
                print_yearly_stats(&stats);
            }

            /* Monthly stats */
            if (args.month)
            {
                temp_stats stats = calculate_stats(head);
                print_monthly_stats(&stats, args.month);
            }

            /* Sorting */
            if (args.sort == 'd' || args.sort == 't')
            {
                sort_list(&head, &tail, args.sort);
            }

            /* Printing */
            if (args.printdb)
            {
                if (args.sort) // сортировка
                    print_list(tail, args.printdb, false); // по возрастанию
                else // без сортировки
                    print_list(tail, args.printdb, true); // в порядке файла
            }
        }
        else
        {
            printf("No valid data found in file\n");
            free_list(&head, &tail);
            return 1;
        }
    }

#endif // DEBUG_MODE

    // -------------- Очистка стека (если нужно) --------//
    free_list(&head, &tail);

    return 0;
}