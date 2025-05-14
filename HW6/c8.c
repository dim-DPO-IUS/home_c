#include <inttypes.h>
#include <stdio.h>

/*Составить функцию, которая переводит латинскую строчную букву в заглавную. И показать пример ее использования.
Формат входных данных: Строка состоящая из английских букв, пробелов и запятых. В конце строки символ точка.
Формат результата: Исходная строка в которой маленькие английские буквы заменены заглавными.
*/

char upper_case(char ch);

int main(void)
{
    char ch;

    while ((ch = getchar()) != '.') {
        putchar(upper_case(ch));
    }

    return 0;
}

char upper_case(char ch)
{
    char ret = ch >= 'a' && ch <= 'z' ? ch - ('a' - 'A') : ch;
    return ret;
}