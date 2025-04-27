#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

/*
Программа для удобной работы с разными системами счисления.
*/

// Функция для перевода символа в число (A=10, B=11, ..., Z=35)
int charToValue(char c) {
    if (isdigit(c)) {
        return c - '0';
    } else {
        return toupper(c) - 'A' + 10;
    }
}

// Функция для перевода числа в символ (10=A, 11=B, ..., 35=Z)
char valueToChar(int num) {
    if (num < 10) {
        return num + '0';
    } else {
        return num - 10 + 'A';
    }
}

// Функция для перевода числа из любой СС в десятичную
long long toDecimal(const char *number, int base) {
    long long decimal = 0;
    int length = strlen(number);
    for (int i = 0; i < length; i++) {
        decimal = decimal * base + charToValue(number[i]);
    }
    return decimal;
}

// Функция для перевода из десятичной СС в любую другую
void fromDecimal(long long decimal, int base, char *result) {
    int index = 0;
    if (decimal == 0) {
        result[index++] = '0';
    } else {
        while (decimal > 0) {
            result[index++] = valueToChar(decimal % base);
            decimal /= base;
        }
    }
    result[index] = '\0';

    // Разворачиваем строку, т.к. записывали остатки в обратном порядке
    for (int i = 0; i < index / 2; i++) {
        char temp = result[i];
        result[i] = result[index - 1 - i];
        result[index - 1 - i] = temp;
    }
}

// Основная функция конвертации
void convertNumber(const char *number, int fromBase, int toBase, char *result) {
    long long decimal = toDecimal(number, fromBase);
    fromDecimal(decimal, toBase, result);
}

int main() {
    char number[100], result[100];
    int fromBase, toBase;

    printf("Введите число: ");
    scanf("%s", number);

    printf("Исходная система счисления (2-36): ");
    scanf("%d", &fromBase);

    printf("Целевая система счисления (2-36): ");
    scanf("%d", &toBase);

    if (fromBase < 2 || fromBase > 36 || toBase < 2 || toBase > 36) {
        printf("Ошибка: система счисления должна быть от 2 до 36.\n");
        return 1;
    }

    convertNumber(number, fromBase, toBase, result);
    printf("Результат: %s\n", result);

    return 0;
}