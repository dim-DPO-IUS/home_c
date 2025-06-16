#include <stdio.h>

/*Составить палиндром
Разработать функцию дана строка из маленьких английских букв. Составить из
символов палиндром максимальной длинны. При составлении палиндрома буквы в
палиндроме должны быть расположены в лексикографическом порядке. Записать ответ
в файл output.txt. Формат входных данных Строка из маленьких английских букв. Не
более 1000 символов. Формат результата Строка из маленьких английских букв.*/

#define MAX 1001
const char *input_file = "input.txt";
const char *output_file = "output.txt";
// Построитель палиндромов
void build_palindrome(const char *s, char *out);

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
    char s[MAX], res[MAX];

    fscanf(input, "%s", s);
    build_palindrome(s, res);
    fprintf(output, "%s", res);

    //---------------------------
    fclose(input);
    fclose(output);
    return 0;
}

//-----------------------------------------------------

void build_palindrome(const char *s, char *out)
{
    int cnt[26] = {0};
    int i, p = 0;

    while (*s)
        cnt[*s++ - 'a']++;

    for (i = 0; i < 26; i++)
    {
        while (cnt[i] >= 2)
        {
            out[p++] = i + 'a';
            cnt[i] -= 2;
        }
    }

    int middle_pos = p;
    for (i = 0; i < 26; i++)
    {
        if (cnt[i] > 0)
        {
            out[p++] = i + 'a';
            break;
        }
    }

    for (i = middle_pos - 1; i >= 0; i--)
    {
        out[p++] = out[i];
    }

    out[p] = '\0';
}
