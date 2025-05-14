#include <inttypes.h>
#include <stdio.h>

/*Скобки
Проверить строку состоящую из скобок "(" и ")" на корректность.

Формат входных данных: На вход подается строка состоящая из символов '(', ')' и заканчивающаяся символом '.'. Размер строки не более 1000 символов.

Формат результата: Необходимо напечатать слово YES если скобки расставлены верно и NO в противном случае.
*/

uint8_t needed_bracket(char bracket);

int main(void)
{
    char bracket;
    uint16_t set = 0;

    while ((bracket = getchar()) != '.') {
        set = needed_bracket(bracket);
    }

    printf("%s\n", set ? "YES" : "NO");
    return 0;
}

uint8_t needed_bracket(char bracket)
{
    static uint16_t set_bracket = 0;

    if (set_bracket == 0 && bracket == ')')
        return 0;

    bracket == '(' ? set_bracket++ : set_bracket--;
    return !set_bracket ? 1 : 0;
}