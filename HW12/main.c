#include "temp_api.h"

#define MAX_ENTRIES 100

int main(int argc, char* argv[])
{
    /* Initialize database */
    sensor_t database[MAX_ENTRIES];
    int number = add_records(database, 20); // Add 20 random records

    /* Parse command line arguments */
    cmd_args_t args;
    int result = parse_arguments(argc, argv, &args);

    /* Handle parser results */
    if(result == -1)
    {
        return 1;
    }
    else if(result == 1)
    {
        return 0;
    }

    /* Process command line options */
    if(args.month) // статистика за месяц
    {
        print_stats(database, number, args.month, 0);
    }
    else if(args.year) // статистика за год
    {
        print_stats(database, number, 0, args.year);
    }
    else if(args.printdb) // печать первых args.printdb записей
    {
        args.printdb > number ? args.printdb = number : number;
        print(database, args.printdb);
    }
    else if(args.filename) // имя файла
    {
        printf("%s\n", args.filename);
    }
    else
    {
        printf("No valid command specified. Use -h for help.\n");
    }
    return 0;
}