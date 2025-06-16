#include <stdio.h>

/*Soundex
Известный алгоритм Soundex (https://ru.wikipedia.org/wiki/Soundex) определяет,
похожи ли два английских слова по звучанию. На вход он принимает слово и
заменяет его на некоторый четырёхсимвольный код. Если коды двух слов совпадают,
то слова, как правило, звучат похоже.

Вам требуется реализовать этот алгоритм. Он работает так:

Первая буква слова сохраняется.
В остальной части слова:
буквы, обозначающие, как правило, гласные звуки: a, e, h, i, o, u, w и y —
отбрасываются; оставшиеся буквы (согласные) заменяются на цифры от 1 до 6,
причём похожим по звучанию буквам соответствуют одинаковые цифры:
1: b, f, p, v
2: c, g, j, k, q, s, x, z
3: d, t
4: l
5: m, n
6: r
Любая последовательность одинаковых цифр сокращается до одной такой цифры.
Итоговая строка обрезается до первых четырёх символов. Если длина строки меньше
требуемой, недостающие символы заменяются знаком 0. Примеры: аmmonium → ammnm →
a5555 → a5 → a500 implementation → implmnttn → i51455335 → i514535 → i514

Формат входных данных Во входном файле input.txt находится одно непустое слово,
записанное строчными латинскими буквами. Длина слова не превосходит 20 символов.

Формат результата Напечатайте четырёхбуквенный код, соответствующий слову в файл
output.txt.*/

const char *input_file = "input.txt";
const char *output_file = "output.txt";

// Алгорит Soundex (https://ru.wikipedia.org/wiki/Soundex)
void soundex(const char *word, char *code);

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
    char word[21]; // Максимум 20 символов + '\0'
    fscanf(input, "%20s", word);

    char code[5]; // 4 символа + '\0'
    soundex(word, code);

    fprintf(output, "%s", code);
    //---------------------------
    fclose(input);
    fclose(output);
    return 0;
}

//-----------------------------------------------------

void soundex(const char *word, char *code)
{
    // Таблица соответствия букв и цифр
    const char *soundex_table = "01230120022455012623010202";
    int code_pos = 1;
    char prev_digit = '0';

    // Сохраняем первую букву
    code[0] = word[0];

    // Обрабатываем остальные буквы
    for (int i = 1; word[i] != '\0' && code_pos < 4; i++)
    {
        char current_char = word[i];

        // Пропускаем гласные и похожие буквы
        if (current_char == 'a' || current_char == 'e' || current_char == 'h' ||
            current_char == 'i' || current_char == 'o' || current_char == 'u' ||
            current_char == 'w' || current_char == 'y')
        {
            continue;
        }

        // Преобразуем букву в цифру
        char current_digit = soundex_table[current_char - 'a'];

        // Пропускаем повторяющиеся цифры
        if (current_digit != prev_digit)
        {
            code[code_pos++] = current_digit;
            prev_digit = current_digit;
        }
    }

    // Заполняем оставшиеся позиции нулями
    while (code_pos < 4)
    {
        code[code_pos++] = '0';
    }

    code[4] = '\0';
}