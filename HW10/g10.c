#include <stdio.h>

/*Самое длинное слово
В файле input.txt дана строка слов, разделенных пробелами. Найти самое длинное
слово и вывести его в файл output.txt. Случай, когда самых длинных слов может
быть несколько, не обрабатывать.

Формат входных данных Строка из английских букв и пробелов. Не более 1000
символов.

Формат результата Одно слово из английских букв.*/

const char *input_file = "input.txt";
const char *output_file = "output.txt";
//-----------------------------------------------------

// Подсчет количества слов разделенных пробелом
int count_words(FILE *input);
// Индекс самого длинного слова
// num: количество слов
int longest_word_idx(FILE *input, int num);
// Пропустить N слов
// После выполнения ф-ии указатель будет на начале N+1 слова
void skip_N_words(FILE *input, int N);

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

    int cnt = count_words(input); // Кол-во слов
    int inx = longest_word_idx(input, cnt); // Индекс самого длинного слова
    skip_N_words(input, inx); // Пропустить все слова до искомого

    int ch;
    while ((ch = fgetc(input)) != EOF && ch != ' ' && ch != '\r' && ch != '\n')
        fputc(ch, output);

    //---------------------------
    fclose(input);
    fclose(output);
    return 0;
}

//-----------------------------------------------------

int count_words(FILE *input)
{
    int cnt = 0;
    while (fscanf(input, "%*s") != EOF)
        cnt++;

    rewind(input);
    return cnt;
}

int longest_word_idx(FILE *input, int num)
{
    int ch;
    int max = 0, inx = 0, count = 0;
    // Кол-во букв в каждом слове: ищем индекс (inx) самого длинного слова
    for (int i = 0; i < num; i++)
    {
        while ((ch = fgetc(input)) != EOF && ch != ' ' && ch != '\r' &&
               ch != '\n')
            count++;

        if (count > max)
        {
            max = count;
            inx = i;
        }
        count = 0;
    }
    rewind(input);
    return inx;
}

void skip_N_words(FILE *input, int N)
{
    // Пропускаем inx слов (читаем в никуда) и следующие за ними пробелы.
    // Указатель на начале N+1 слова.
    for (int i = 0; i < N; i++)
        fscanf(input, "%*s ");
}