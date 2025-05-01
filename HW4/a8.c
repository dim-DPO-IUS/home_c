#include <stdio.h>
#include <inttypes.h>

//Наибольшее из трех чисел

int main(void)
{
	int32_t a=0,b=0,c=0;
    int32_t max=0;

	scanf("%"SCNd32"%"SCNd32"%"SCNd32, &a,&b,&c);

    max = a>=b?a:b;
    max = c>=max?c:max;

	printf("%"PRId32"\n", max);

	return 0;
}