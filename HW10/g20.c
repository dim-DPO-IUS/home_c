#include <stdio.h>

/*Проверка на палиндром
Считать предложение из файла input.txt и определить можно ли из английских букв
предложения записанного в файле получить одно слово - палиндром. Ответ
напечатать на стандартный поток вывода. Требуется реализовать логическую функцию
и применить ее. is_palindrom(string)

Формат входных данных Строка из маленьких английских букв и пробелов. Не более
1000 символов.

Формат результата YES или NO*/

#define MAX 1001
const char *input_file = "input.txt";
const char *output_file = "output.txt";

int is_letter(char c);
void letter_stats(char *s, int freq_map[]);
int is_palindrom(char *s);

//-----------------------------------------------------
int main(void)
{
    FILE *input = fopen(input_file, "r");
    FILE *output = fopen(output_file, "w");
    if (input == NULL || output == NULL)
    {
        perror("Ошибка открытия файла");
        return 1;
    }
    //---------------------------
    char s[MAX] = {'\0'};
    fgets(s, sizeof(s), input);
    printf("%s", is_palindrom(s) ? "YES" : "NO");
    //---------------------------
    fclose(input);
    fclose(output);
    return 0;
}

//-----------------------------------------------------

int is_letter(char c)
{
    return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z');
}

void letter_stats(char *s, int freq_map[])
{
    while (*s)
    {
        char c = *s++;
        if (is_letter(c)) freq_map[c - 'a']++;
    }
}

int is_palindrom(char *s)
{
    int freq_map[26] = {0};
    letter_stats(s, freq_map);
    int cnt = 0;
    for (int i = 0; i < 26; i++)
        freq_map[i] % 2 ? cnt++ : cnt;
    return cnt <= 1 ? 1 : 0;
}