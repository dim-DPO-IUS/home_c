#include <stdio.h>
#include <inttypes.h>

// Ввести три числа и определить, верно ли, что они вводились 
// в порядке возрастания.

int main(void)
{
    int32_t a=0,b=0,c=0;
    
    scanf("%d%d%d", &a, &b, &c);
    printf("%s\n", a<b && b<c?"YES":"NO");

    return 0;
}