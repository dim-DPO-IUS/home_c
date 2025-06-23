#include "temp_api.h"

#define MAX_ENTRIES 100

int main(int argc, char* argv[])
{
    sensor database[MAX_ENTRIES]; // массив структур для базы данных
    int number = add_records(database, 20); // добавить 20 случайных записей

    cmd_args args; // структура для парсера аргументов
    int result = parse_arguments(argc, argv, &args); // парсим аргументы
    // ----------------------------------------------

    if(result == -1) // ошибки
        return 1;
    else if(result == 1) // справка
        return 0;
    else if(args.month) // статистика за месяц
        print_stats(database, number, args.month, 0);
    else if(args.year) // статистика за год
        print_stats(database, number, 0, args.year);
    else if(args.printdb) // печать первых args.printdb записей
    {
        args.printdb > number ? args.printdb = number : number;
        print(database, args.printdb);
    }
    else if(args.filename) // имя файла
        printf("%s\n", args.filename);

    return 0;
}