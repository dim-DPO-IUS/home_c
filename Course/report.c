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
        free_list(&head, &tail);
        return 0;
    }

    // Обработка данных согласно режиму
    process_data_mode(head, tail, &args, &load_info);

    free_list(&head, &tail);
    return 0;
}