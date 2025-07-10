#include "temp_function.h"

int main(int argc, char* argv[])
{
    node *head = NULL, *tail = NULL;
    cmd_args args = { 0 };
    load_stats load_info = { 0 };

    // Парсинг аргументов
    int parse_result = parse_arguments(argc, argv, &args);

    // Обработка специальных случаев
    switch (parse_result)
    {
    case 2: printf(START_MSG); return 0; // Запуск без аргументов
    case 1: printf(HELP_MSG); return 0; // Справка -h
    case -1: // Ошибки
        fprintf(stderr, "Error: Invalid arguments\n");
        printf(HELP_MSG);
        return 1;
    }

    // Загрузка данных
    if (!load_from_csv(args.filename, &head, &tail, ';', &load_info))
    {
        printf("No valid data found in file\n");
        goto cleanup;
    }

    // Определение режима работы
    switch (args.mode)
    {
    case MODE_FILE: { // Только файл (-f)
        print_load_stats(&load_info);
        temp_stats stats = calculate_stats(head);
        print_monthly_stats(&stats, 0);
        print_yearly_stats(&stats);
        break;
    }
    case MODE_FILE_MONTH: { // Файл + месяц (-f -m)
        temp_stats stats = calculate_stats(head);
        print_monthly_stats(&stats, args.month);
        break;
    }
    case MODE_FILE_PRINT: { // Файл + печать (-f -p)
        print_list(tail, args.printdb, true);
        break;
    }
    case MODE_FILE_SORT_PRINT: { // Файл + сортировка + печать (-f -s -p)
        sort_list(&head, &tail, args.sort);
        print_list(tail, args.printdb, false);
        break;
    }
    default: // Неизвестная комбинация
        fprintf(stderr, "Warning: Unknown mode combination (0x%X)\n", args.mode);
    }

cleanup:
    free_list(&head, &tail);
    return 0;
}