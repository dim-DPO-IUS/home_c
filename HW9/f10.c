#include <stdio.h>

/*Упаковать строку
Дана строка состоящая из маленьких латинских букв 'a'..'z'. В конце строки
точка. Необходимо заменить повторяющиеся буквы на <буква><количество повторений>

Формат входных данных: Входная строка состоящая из букв 'a'-'z' не превышающая
1000 символов. В конце строки символ '.' Формат результата: Результат состоящий
из букв и чисел, без пробелов*/

enum
{
    SIZE = 1001
};

void compress_string(char input[], char output[]);

// --------------------------------

int main(void)
{
    char s[SIZE] = {0};
    char output[SIZE * 2]; // В худшем случае каждый символ заменяется на 2
                           // символа (a1)
    scanf("%1000s", s); // Читаем строку, но не более 1000 символов
    compress_string(s, output);
    printf("%s\n", output);
    return 0;
}

// --------------------------------

void compress_string(char input[], char output[])
{
    int i = 0, j = 0;
    while (input[i] != '.')
    { 
        char current_char = input[i];
        int count = 1;
        i++;
        
        while (input[i] == current_char)
        {
            count++;
            i++;
        }
        
        output[j++] = current_char;
        j += sprintf(output + j, "%d", count);
    }
    output[j] = '\0'; 
}
