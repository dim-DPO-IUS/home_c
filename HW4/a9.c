#include <stdio.h>
#include <inttypes.h>

// Наибольшее из пяти чисел

int main(void)
{
	int32_t a=0,b=0,c=0,d=0,e=0;
    int32_t max=0;

	scanf("%d%d%d%d%d", &a,&b,&c,&d,&e);

    max = a>=b?a:b;
    max = c>=max?c:max;
    max = d>=max?d:max;
    max = e>=max?e:max;

	printf("%d\n", max);

	return 0;
}