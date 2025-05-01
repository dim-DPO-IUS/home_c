#include<stdio.h>
#include<inttypes.h>

// Ввести номер месяца и вывести название времени года
//  winter, spring, summer, autumn

int main(void)
{
    int8_t m=0;

    scanf("%"SCNd8, &m);

    if(m>2 && m<=5)
        printf("spring\n");
    else if(m>5 && m<=8)
        printf("summer\n");
    else if(m>8 && m<=11)
        printf("autumn\n");
    else
        printf("winter\n");

    return 0;
}