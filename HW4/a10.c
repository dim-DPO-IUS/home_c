#include <stdio.h>
#include <inttypes.h>

// Наименьшее из пяти чисел

int main(void)
{
	int32_t a=0,b=0,c=0,d=0,e=0;
    int32_t min=0;

	scanf("%d%d%d%d%d", &a,&b,&c,&d,&e);

    min = a<=b?a:b;
    min = c<=min?c:min;
    min = d<=min?d:min;
    min = e<=min?e:min;

	printf("%d\n", min);

	return 0;
}