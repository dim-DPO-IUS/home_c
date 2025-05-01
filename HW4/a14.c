#include <stdio.h>
#include <inttypes.h>

// Дано трехзначное число, напечатать макисмальную цифру

int main(void)
{
	uint32_t a=0; // Целое положительное трехзначное число
    uint8_t num1=0,num2=0,num3=0; 
    uint8_t max_num=0;

	scanf("%u", &a);

    num1 = a/100;
    num2 = a%100/10;
    num3 = a%10; 

    max_num = num1 > num2 ? num1:num2;
    max_num = num3 > max_num ? num3:max_num;

    printf("%"PRIu8"\n", max_num);

	return 0;
}