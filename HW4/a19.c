#include<stdio.h>
#include<inttypes.h>

// Даны стороны треугольника a, b, c. 
// Определить существует ли такой треугольник.

int main(void)
{
    int32_t a=0,b=0,c=0;
    scanf("%d%d%d", &a,&b,&c);

    // Длина любой стороны треугольника всегда меньше суммы 
    // длин 2-х других сторон.
    printf("%s\n", a<(b+c) && b<(a+c) && c<(a+b)?"YES":"NO");

    return 0;
}