#include <stdio.h>
/*По одному разу
В файле input.txt даны два слова не более 100 символов каждое, разделенные
одним пробелом. Найдите только те символы слов, которые встречаются в обоих
словах только один раз. Напечатайте их через пробел в файл output.txt в
лексикографическом порядке.
Формат входных данных Два слова из маленьких английских букв через пробел.
Длинна каждого слова не больше 100 символов.
Формат результата Маленькие английские буквы через пробел.*/

const char *input_file = "input.txt";
const char *output_file = "output.txt";
//
void count_chars(const char *word, int counts[]);
void find_unique_chars(const char *word, int unique[]);
//--------------------------------------------
int main(void)
{
    //---------------------
    FILE *input = fopen(input_file, "r");
    FILE *output = fopen(output_file, "w");

    if (input == NULL || output == NULL)
    {
        perror("Ошибка открытия файла");
        return 1;
    }
    //---------------------

    char word1[101], word2[101];
    fscanf(input, "%100s %100s", word1, word2);

    int unique1[26] = {0}, unique2[26] = {0};

    find_unique_chars(word1, unique1);
    find_unique_chars(word2, unique2);

    int first = 1;
    for (int i = 0; i < 26; i++)
    {
        if (unique1[i] && unique2[i])
        {
            if (!first) fprintf(output, " ");
            fprintf(output, "%c", 'a' + i);
            first = 0;
        }
    }

    //---------------------
    fclose(input);
    fclose(output);

    return 0;
}

//-----------------------------------------------------

void count_chars(const char *word, int counts[])
{
    for (int i = 0; word[i] != '\0'; i++)
    {
        counts[word[i] - 'a']++;
    }
}

void find_unique_chars(const char *word, int unique[])
{
    int counts[26] = {0};
    count_chars(word, counts);

    for (int i = 0; i < 26; i++)
    {
        unique[i] = (counts[i] == 1);
    }
}