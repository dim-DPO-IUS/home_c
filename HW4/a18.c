#include<stdio.h>
#include<inttypes.h>


int main(void)
{
    int32_t a=0,b=0;
    scanf("%d%d", &a, &b);

    if(a==b)
        printf("Equal\n");
    else
        printf("%s\n", a>b?"Above":"Less");

    return 0;
}