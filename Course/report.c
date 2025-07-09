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
    if (!load_from_csv("temperature_big.csv", &head, &tail, ';', &load_info))
    {
        fprintf(stderr, "Debug mode: Failed to load test file\n");
        free_list(&head, &tail);
        return 1;
    }
    print_load_stats(&load_info);
    // ======================================================================
#else
    /* Parse and process arguments */
    cmd_args args;
    int parse_result = parse_arguments(argc, argv, &args);

    /* Handle special cases first */
    if (parse_result == 2)
    { // No arguments
        printf(START_MSG);
        free_list(&head, &tail);
        return 0;
    }
    if (parse_result == 1)
    { // Help shown
        free_list(&head, &tail);
        return 0;
    }
    if (parse_result == -1)
    { // Error
        free_list(&head, &tail);
        return 1;
    }

    /* Main processing - only if parse_result == 0 */
    if (!args.filename)
    {
        free_list(&head, &tail);
        return 1;
    }

    load_stats load_info;
    if (!load_from_csv(args.filename, &head, &tail, ';', &load_info))
    {
        printf("No valid data found in file\n");
        free_list(&head, &tail);
        return 1;
    }

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

    /* Printing - improved logic */
    if (args.printdb)
    {
        bool reverse_order = !args.sort; // Reverse if not sorted
        print_list(tail, args.printdb, reverse_order);
    }

#endif // DEBUG_MODE

    // -------------- Очистка стека (если нужно) --------//
    free_list(&head, &tail);

    return 0;
}